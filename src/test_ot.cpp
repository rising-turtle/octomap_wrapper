/*
 *  Feb.2 2016, David Z
 *
 *  test add a pcd into a ot map
 *
 * */

#include <pcl/io/pcd_io.h>
#include "ColorOctreeImpl.h"
#include <iostream>
#include <fstream>
#include "octomap/OcTree.h"

using namespace std;
using namespace octomap;

ColorOctreeImpl* createOctreeImpl();

void simple_test();

int main(int argc, char * argv[])
{
  if(argc < 2)
  {
    cout<<"test_ot.cpp: needs to specify a *.pcd file!"<<endl;
    return -1;
  }
  
  ColorOctreeImpl* ot_impl = createOctreeImpl();
  // ColorOctreeImpl ot_impl(0.5);
  octowrapper::color_pc_ptr pc(new octowrapper::color_point_cloud); 
  if(pcl::io::loadPCDFile(argv[1], *pc) == 0) 
  {
    cout<<"test_ot.cpp: succeed to load pcd file: "<<argv[1]<<endl;
    ot_impl->insertPointCloud(*pc);
    ot_impl->updateInnerOccupancy();
  }else
  {
    cout<<"test_ot.cpp: failed to load pcd file: "<<argv[1]<<endl;
  }
  
  // ofstream ouf("octomap.ot");
  // ofstream oufb("octomap_bin.bt");
  // ot_impl->writeData(ouf);
  // string s("octomap_bin.bt");
  ot_impl->writeBinary("octomap_bin.bt");

  // simple_test();

  return 0;
}

void simple_test()
{
  
    // OcTree tree (0.1);  // create empty tree with resolution 0.1
    // ColorOcTree tree(0.1);
    ColorOctreeImpl tree(0.1);
    for (int x=-20; x<20; x++) {
      for (int y=-20; y<20; y++) {
        for (int z=-20; z<20; z++) {
          point3d endpoint ((float) x*0.05f, (float) y*0.05f, (float) z*0.05f);
          tree.updateNode(endpoint, true); // integrate 'occupied' measurement
        }
      }
    }

    for (int x=-30; x<30; x++) {
      for (int y=-30; y<30; y++) {
        for (int z=-30; z<30; z++) {
          point3d endpoint ((float) x*0.02f-1.0f, (float) y*0.02f-1.0f, (float) z*0.02f-1.0f);
          tree.updateNode(endpoint, false);  // integrate 'free' measurement
        }
      }
    }

    cout << endl;
    tree.writeBinary("simple_tree.bt");
    cout << "wrote example file simple_tree.bt" << endl << endl;
    cout << "now you can use octovis to visualize: octovis simple_tree.bt"  << endl;
}

ColorOctreeImpl* createOctreeImpl()
{
  ColorOctreeImpl * ot_impl = new ColorOctreeImpl(0.05); 
  ot_impl->setClampingThresMin(0.001); 
  ot_impl->setClampingThresMax(0.999); 
  ot_impl->setOccupancyThres(0.8); 
  ot_impl->setProbHit(0.9); 
  ot_impl->setProbMiss(0.4); 
  return ot_impl;
}



