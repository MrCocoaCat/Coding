/* \author Radu Bogdan Rusu
 * adaptation Raphael Favier*/
#include <boost/make_shared.hpp>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/filter.h>
#include <pcl/features/normal_3d.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/icp_nl.h>
#include <pcl/registration/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>
using pcl::visualization::PointCloudColorHandlerGenericField;
using pcl::visualization::PointCloudColorHandlerCustom;
//简单类型定义
typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;
typedef pcl::PointNormal PointNormalT;
typedef pcl::PointCloud<PointNormalT> PointCloudWithNormals;
//这是一个辅助教程，因此我们可以负担全局变量

//创建可视化工具
pcl::visualization::PCLVisualizer *p;

//定义左右视点
int vp_1, vp_2;
//处理点云的方便的结构定义
struct PCD
{
  PointCloud::Ptr cloud;
  std::string f_name;
  PCD() : cloud (new PointCloud) {};
};

struct PCDComparator
{
  bool operator () (const PCD& p1, const PCD& p2)
  {
    return (p1.f_name < p2.f_name);
  }
};

//以< x, y, z, curvature >形式定义一个新的点
class MyPointRepresentation : public pcl::PointRepresentation <PointNormalT>
{
  using pcl::PointRepresentation<PointNormalT>::nr_dimensions_;
public:
  MyPointRepresentation ()
  {
    //定义尺寸值
    nr_dimensions_ = 4;
  }
  //覆盖copyToFloatArray方法来定义我们的特征矢量
  virtual void copyToFloatArray (const PointNormalT &p, float * out) const
  {
    // < x, y, z, curvature >
    out[0] = p.x;
    out[1] = p.y;
    out[2] = p.z;
    out[3] = p.curvature;
  }
};

/** 在可视化窗口的第一视点显示源点云和目标点云**/
//void showCloudsLeft(const PointCloud::Ptr cloud_target, const PointCloud::Ptr cloud_source)
//{
//  p->removePointCloud ("vp1_target");
//  p->removePointCloud ("vp1_source");
//
//  PointCloudColorHandlerCustom<PointT> tgt_h (cloud_target, 0, 255, 0);
//  PointCloudColorHandlerCustom<PointT> src_h (cloud_source, 255, 0, 0);
//
//  p->addPointCloud (cloud_target, tgt_h, "vp1_target", vp_1);
//  p->addPointCloud (cloud_source, src_h, "vp1_source", vp_1);
//
//  PCL_INFO ("Press q to begin the registration.\n");
//  p-> spin();
//}
//
///**在可视化窗口的第二视点显示源点云和目标点云* */
//void showCloudsRight(const PointCloudWithNormals::Ptr cloud_target, const PointCloudWithNormals::Ptr cloud_source)
//{
//  p->removePointCloud ("source");
//  p->removePointCloud ("target");
//  PointCloudColorHandlerGenericField<PointNormalT> tgt_color_handler (cloud_target, "curvature");
//  if (!tgt_color_handler.isCapable ())
//      PCL_WARN ("Cannot create curvature color handler!");
//  PointCloudColorHandlerGenericField<PointNormalT> src_color_handler (cloud_source, "curvature");
//  if (!src_color_handler.isCapable ())
//      PCL_WARN ("Cannot create curvature color handler!");
//  p->addPointCloud (cloud_target, tgt_color_handler, "target", vp_2);
//  p->addPointCloud (cloud_source, src_color_handler, "source", vp_2);
//  p->spinOnce();
//}



/* ---[ */
int main (int argc, char** argv)
{
  //加载数据，声明存放PCD结构体的容器
  std::vector<PCD, Eigen::aligned_allocator<PCD> >  data;
  ///调用loadData 函数，将数据放入容器中
    for (int i = 1; i < argc; i++)
    {
        std::string fname = std::string (argv[i]);
        // 至少需要5个字符长（因为.plot就有 5个字符）
         //加载点云并保存在总体的模型列表中
        PCD m;
        m.f_name = argv[i];//第几个点云就是第几个参数
        pcl::io::loadPCDFile (argv[i], *m.cloud); //读点云到结构体
        //从点云中移除NAN点
        std::vector<int> indices;
        pcl::removeNaNFromPointCloud(*m.cloud,*m.cloud, indices); //调用removeNaNFromPointCloud函数
        data.push_back (m); //放入models中，这是个存放点云的数组
    }


  PCL_INFO ("Loaded %d datasets.", (int)data.size ());

  //创建一个PCL可视化对象


  PointCloud::Ptr result (new PointCloud);
  PointCloud::Ptr source;
  PointCloud::Ptr target;

  Eigen::Matrix4f GlobalTransform = Eigen::Matrix4f::Identity ();
  Eigen::Matrix4f pairTransform;

  for (size_t i = 1; i < data.size (); ++i)
  {
      //
    source = data[i-1].cloud;
    target = data[i].cloud;

    ///ICP

    //
    //为了一致性和高速的下采样
    //注意：为了大数据集需要允许这项
    PointCloud::Ptr src (new PointCloud);
    PointCloud::Ptr tgt (new PointCloud);
    pcl::VoxelGrid<PointT> grid;
    //判断是否降采样
    if (0)
    {
      grid.setLeafSize (0.05, 0.05, 0.05);
      grid.setInputCloud (source); //对第一个点云采样
      grid.filter (*src);

      grid.setInputCloud (target);//对第二个点云采样
      grid.filter (*tgt);
    }
    else
    {
      src = source;
      tgt = target;
    }

    //定义带法线的点云数据
    PointCloudWithNormals::Ptr points_with_normals_src (new PointCloudWithNormals);
    PointCloudWithNormals::Ptr points_with_normals_tgt (new PointCloudWithNormals);

    pcl::NormalEstimation<PointT, PointNormalT> norm_est;
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());

   //计算曲面法线和曲率
    //为src 点云添加法线
    norm_est.setSearchMethod (tree);//法线估计方式为kdtree
    norm_est.setKSearch (30);
    norm_est.setInputCloud (src);
    norm_est.compute (*points_with_normals_src);//估计法线
    pcl::copyPointCloud (*src, *points_with_normals_src); //将法线估计放入src中
    //为tgt 点云添加法线
    norm_est.setInputCloud (tgt);
    norm_est.compute (*points_with_normals_tgt);
    pcl::copyPointCloud (*tgt, *points_with_normals_tgt);//将法线估计放入tgt中

    //举例说明我们自定义点的表示（以上定义）
    MyPointRepresentation point_representation;
    //调整'curvature'尺寸权重以便使它和x, y, z平衡
    float alpha[4] = {1.0, 1.0, 1.0, 1.0};
    point_representation.setRescaleValues (alpha);

    // 配准
// setMaximumIterations (intnr_iterations) 第1个约束，迭代次数，几十上百都可能出现。
// setTransformationEpsilon (doubleepsilon) 第2个约束，这个值一般设为1e-6或者更小。
// setEuclideanFitnessEpsilon (doubleepsilon) 第3个约束，前后两次迭代误差的差值。

    pcl::IterativeClosestPointNonLinear<PointNormalT, PointNormalT> icp; //ICP配准对象
    icp.setTransformationEpsilon (1e-6);
    //将两个对应关系之间的(src<->tgt)最大距离设置为10厘米
    //注意：根据你的数据集大小来调整
    icp.setMaxCorrespondenceDistance (0.1);
    //设置点表示
    icp.setPointRepresentation (boost::make_shared<const MyPointRepresentation> (point_representation));
    icp.setMaximumIterations (2); //迭代次数
    //设置匹配的点云
    icp.setInputSource (points_with_normals_src);
    icp.setInputTarget (points_with_normals_tgt);

    PointCloudWithNormals::Ptr Final ;
    icp.align(*Final);                             //打印配准相关输入信息
      icp.getFinalTransformation ();

      //在一个循环中运行相同的最优化并且使结果可视化
    Eigen::Matrix4f Ti = Eigen::Matrix4f::Identity (),
    Eigen::Matrix4f prev;
    Eigen::Matrix4f targetToSource;

    PointCloudWithNormals::Ptr reg_result = points_with_normals_src;

    Ti = icp.getFinalTransformation () * Ti;
    cout<<Ti<<endl;
    ///ICP END
    std::stringstream ss;
    ss << i << ".pcd";
    pcl::io::savePCDFile (ss.str (), *result, true);
  }

}
/* ]--- */
