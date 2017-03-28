#include <vtkSphereSource.h>
#include <vtkRendererCollection.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include "geometry/vtk_utils.h"
#include "geometry/vtk_debug.h"
#include "synthesis/mesh_to_gcode.h"
#include "system/parse_stl.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parallel_dialog.h"
#include "stock_dialog.h"
#include "tool_page.h"

#include <QHBoxLayout>
#include <QFileDialog>

using namespace gca;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), initial_stock(-1, -1, -1, gca::ACETAL) {

  set_system_allocator(&alloc);

  QPushButton* load_stl_button = new QPushButton("Load STL");
  add_tool_button = new QPushButton("Add tool", this);
  define_vice_button = new QPushButton("Define vice", this);
  add_parallel_button = new QPushButton("Add parallel plate", this);
  define_stock_button = new QPushButton("Define stock", this);
  generate_plan_button = new QPushButton("Create plan", this);

  QVBoxLayout* update_buttons = new QVBoxLayout();
  update_buttons->addWidget(load_stl_button);
  update_buttons->addWidget(add_tool_button);
  update_buttons->addWidget(define_vice_button);
  update_buttons->addWidget(add_parallel_button);
  update_buttons->addWidget(define_stock_button);
  update_buttons->addWidget(generate_plan_button);

  main_part_layout = new QVBoxLayout;
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(1, 1, 1);

  part_window = new QVTKWidget(this, Qt::Widget);
  part_window->GetRenderWindow()->AddRenderer(renderer);
  part_window->show();
  part_window->update();
    
  main_part_layout->addWidget(part_window);

  vtk_layout = new QVBoxLayout;

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addLayout(update_buttons);
  layout->addLayout(main_part_layout);
  layout->addLayout(vtk_layout);
  // layout->addLayout(in_progress);
  // layout->addLayout(completed);

  setCentralWidget(new QWidget);
  centralWidget()->setLayout(layout);

  connect(load_stl_button, SIGNAL (released()), this, SLOT (load_stl()));
  connect(generate_plan_button, SIGNAL (released()), this, SLOT (generate_plan()));
  connect(add_tool_button, SIGNAL (released()), this, SLOT (add_tool()));
  connect(add_parallel_button, SIGNAL (released()), this, SLOT (add_parallel()));
  connect(define_stock_button, SIGNAL (released()), this, SLOT (define_stock()));
  
  
  // connect(accept_button, SIGNAL (released()), this, SLOT (handle_accept()));
  // connect(reject_button, SIGNAL (released()), this, SLOT (handle_reject()));
  // connect(set_done_button, SIGNAL (released()), this, SLOT (handle_set_done()));

  // // active_mesh =
  // //   parse_stl("/Users/dillon/CppWorkspace/gca/test/stl-files/onshape_parts/artusitestp1 - Part 1.stl", 0.0001);
  
  // // active_mesh =
  // //   parse_stl("/Users/dillon/CppWorkspace/gca/test/stl-files/onshape_parts/caliperbedlevelingi3v2_fixed - Part 1.stl", 0.0001);

  // active_mesh = parse_stl("/Users/dillon/CppWorkspace/gca/test/stl-files/onshape_parts/SmallReverseCameraMount - Part 1.stl", 0.0001);

  // slice_planes = possible_slice_planes(active_mesh);

  // DBG_ASSERT(slice_planes.size() > 0);

  // active_plane = slice_planes.back();
  // slice_planes.pop_back();

  // active_plane_actor = plane_actor(vtk_plane(active_plane));

  // active_mesh_polydata = polydata_for_trimesh(active_mesh);
  // color_polydata(active_mesh_polydata, 0, 255, 0);

  // vtkSmartPointer<vtkPolyDataMapper> mapper = 
  //   vtkSmartPointer<vtkPolyDataMapper>::New();
  // mapper->SetInputData(active_mesh_polydata);

  // active_mesh_actor = 
  //   vtkSmartPointer<vtkActor>::New();
  // active_mesh_actor->SetMapper(mapper);

  // renderer = vtkSmartPointer<vtkRenderer>::New();

  // renderer->SetBackground(1, 1, 1);
  // renderer->AddActor(active_mesh_actor);
  // renderer->AddActor(active_plane_actor);

  // vtk_window->GetRenderWindow()->AddRenderer(renderer);

  // vtk_window->show();

}

// std::string to_string(const point pt) {
//   return "(" + std::to_string(pt.x) + ", " + std::to_string(pt.y) + ", " + std::to_string(pt.z) + ")";
// }

// std::string to_string(const plane& p) {
//   return "Normal = " + to_string(p.normal()) + "\nPt = " + to_string(p.pt());
// }

// void MainWindow::update_active_plane(const gca::plane p) {
//   in_progress_heading->setText(to_string(p).c_str());
//   renderer->RemoveActor(active_plane_actor);
//   active_plane_actor = plane_actor(vtk_plane(p));
//   renderer->AddActor(active_plane_actor);
//   vtk_window->update();
// }

// void MainWindow::clear_active_plane() {
//   renderer->RemoveActor(active_plane_actor);
// }

// void MainWindow::update_active_mesh(const gca::triangular_mesh& new_mesh) {

//   active_mesh = new_mesh;

//   slice_planes = possible_slice_planes(active_mesh);

//   if (slice_planes.size() > 0) {
//     active_plane = slice_planes.back();
//     slice_planes.pop_back();

//     update_active_plane(active_plane);
//   } else {
//     slice_planes = {};
//     clear_active_plane();
//   }

//   active_mesh_polydata = polydata_for_trimesh(active_mesh);
//   color_polydata(active_mesh_polydata, 0, 255, 0);

//   renderer->RemoveActor(active_mesh_actor);
  
//   vtkSmartPointer<vtkPolyDataMapper> mapper = 
//     vtkSmartPointer<vtkPolyDataMapper>::New();
//   mapper->SetInputData(active_mesh_polydata);

//   active_mesh_actor = 
//     vtkSmartPointer<vtkActor>::New();
//   active_mesh_actor->SetMapper(mapper);

//   renderer->AddActor(active_mesh_actor);

//   vtk_window->update();

// }

// void MainWindow::handle_set_done_slice() {

//   auto part_nef = trimesh_to_nef_polyhedron(active_mesh);
//   part_split p_split = build_part_split(part_nef);
//   add_to_filletables(p_split);    
  
//   if (in_progress.size() == 0) {
//     switch_to_fillet_mode();
//     fillet_next_part();
//     return;
//   }

//   // auto next_mesh = nef_to_single_trimesh(in_progress.back().nef);
//   // in_progress.pop_back();

//   slice_next_part();
//   //update_active_mesh(next_mesh);
// }

// void MainWindow::slice_next_part() {

//   if (in_progress.size() == 0) {
//     in_progress_heading->setText("All parts are finished");
//     switch_to_fillet_mode();
//     fillet_next_part();
//     return;
//   }

//   part_split next_part = in_progress.back();
//   in_progress.pop_back();

//   auto mesh = nef_to_single_trimesh(next_part.nef);

//   update_active_mesh(mesh);

// }

// template<typename T>
// void delete_other_inds(std::vector<T>& elems, int ind) {
//   T elem = elems[ind];
//   elems.clear();
//   elems.push_back(elem);
// }

// void MainWindow::handle_accept_fillet() {
//   fillet_group& current_group =
//     active_fillet_part.part.fillet_groups[active_fillet_part.fillet_group_index];

//   delete_other_inds(current_group.possible_fillets, active_fillet_part.fillet_index);

//   clear_active_fillet();

//   fillet_next();
// }

// void MainWindow::handle_reject_fillet() {
//   fillet_group& current_group =
//     active_fillet_part.part.fillet_groups[active_fillet_part.fillet_group_index];

//   current_group.possible_fillets.erase(begin(current_group.possible_fillets) + active_fillet_part.fillet_index);

//   clear_active_fillet();

//   fillet_next();
// }

// void MainWindow::handle_set_done_fillet() {
// }

// void MainWindow::handle_accept() {
//   if (current_mode == SLICE_MODE) {
//     handle_accept_slice();
//   } else if (current_mode == FILLET_MODE) {
//     handle_accept_fillet();
//   } else {
    
//   }

// }

// void MainWindow::handle_reject() {
//   if (current_mode == SLICE_MODE) {
//     handle_reject_slice();
//   } else if (current_mode == FILLET_MODE) {
//     handle_reject_fillet();
//   } else {
//     return;
//   }
  
// }

// void MainWindow::handle_set_done() {
//   if (current_mode == SLICE_MODE) {
//     handle_set_done_slice();
//   } else {
//     DBG_ASSERT(false);
//   }

// }

// void MainWindow::switch_to_fillet_mode() {
//   current_mode = FILLET_MODE;
//   clear_active_plane();
//   accept_button->setText("Accept fillet");
//   reject_button->setText("Reject fillet");
// }

// void MainWindow::clear_active_fillet() {
//   renderer->RemoveActor(active_fillet_actor);
// }

// void MainWindow::clear_active_mesh() {
//   renderer->RemoveActor(active_mesh_actor);
// }

// void MainWindow::set_active_fillet(const active_fillet& af) {

//   update_active_mesh(af.part.part);
//   clear_active_plane();

//   clear_active_fillet();

//   active_fillet_part = af;

//   active_fillet_actor = actor_for_fillet(active_fillet_part.part.part,
// 					 active_fillet_part.current_fillet());

//   renderer->AddActor(active_fillet_actor);
// }

// std::pair<int, int> find_next_fillet_choice(const active_fillet& af) {
//   int fillet_group;
//   for (fillet_group = 0;
//        fillet_group < af.part.fillet_groups.size();
//        fillet_group++) {

//     int num_possible_fillets =
//       af.part.fillet_groups[fillet_group].possible_fillets.size();
//     if (num_possible_fillets > 1) {
//       return std::make_pair(fillet_group, 0);
//     }

//   }


//   return std::make_pair(-1, -1);
// }

// active_fillet MainWindow::next_active_fillet() {
//   filletable_part next = in_progress_fillets.back();
//   in_progress_fillets.pop_back();

//   active_fillet af{next, -1, -1};

//   std::pair<int, int> next_fillets = find_next_fillet_choice(af);

//   DBG_ASSERT(next_fillets.first != -1);
//   DBG_ASSERT(next_fillets.second != -1);

//   af.fillet_group_index = next_fillets.first;
//   af.fillet_index = next_fillets.second;

//   return af;
// }

// void MainWindow::fillet_next() {
//   std::pair<int, int> next_fillets = find_next_fillet_choice(active_fillet_part);

//   if (next_fillets.first == -1) {
//     finished_fillets.push_back(active_fillet_part.part);
//     fillet_next_part();
//     return;
//   }

//   active_fillet_part.fillet_group_index = next_fillets.first;
//   active_fillet_part.fillet_index = next_fillets.second;
//   set_active_fillet(active_fillet_part);
// }

// void MainWindow::fillet_next_part() {
//   if (in_progress_fillets.size() == 0) {
//     in_progress_heading->setText("NOTHING LEFT TO FILLET");
//     set_complete_mode();
//     return;
//   }

//   active_fillet af = next_active_fillet();
//   set_active_fillet(af); //next.part, next.fillet_groups.front().possible_fillets.front());
// }

// std::vector<fillet_group> build_fillet_groups(const triangular_mesh& m) {
//   auto sfc = build_surface_milling_constraints(m);
//   vector<vector<surface> > corner_groups =
//     sfc.hard_corner_groups();

//   vector<surface> sfs = outer_surfaces(m);
//   DBG_ASSERT(sfs.size() > 0);
//   vector<plane> stock_planes = set_right_handed(max_area_basis(sfs));
//   vector<point> dirs;
//   for (auto& p : stock_planes) {
//     dirs.push_back(p.normal());
//     dirs.push_back(-1*p.normal());
//   }

//   vector<fillet_group> fillets;
//   for (auto cg : corner_groups) {

//     vector<vector<shared_edge> > possible_fillets;

//     for (auto access_dir : dirs) {

//       if (!is_centralized(cg)) {

// 	if (all_surfaces_are_millable_from(access_dir, cg)) {
// 	  vector<shared_edge> edges = edges_to_fillet(cg, m, access_dir);
// 	  possible_fillets.push_back(edges);
// 	  //vtk_debug_shared_edges(edges, m);
// 	}
//       }

//     }

//     fillets.push_back({possible_fillets});

//   }

//   return fillets;
// }

// std::vector<filletable_part> build_filletables(const part_split& part) {
//   vector<filletable_part> filletable;
//   for (auto& m : nef_polyhedron_to_trimeshes(part.nef)) {
//     std::vector<fillet_group> fillets = build_fillet_groups(m);
//     filletable.push_back({m, fillets});
//   }

//   return filletable;
// }

// bool is_finished(const filletable_part& part) {
//   if (part.fillet_groups.size() == 0) { return true; }

//   for (auto& f : part.fillet_groups) {
//     if (f.possible_fillets.size() > 1) {
//       return false;
//     }
//   }

//   return true;
// }

// void MainWindow::add_to_filletables(const part_split& part) {
//   vector<filletable_part> filletables =
//     build_filletables(part);

//   for (auto& f : filletables) {
//     if (is_finished(f)) {
//       finished_fillets.push_back(f);
//     } else {
//       in_progress_fillets.push_back(f);
//     }
//   }
// }

// void MainWindow::add_to_queues(const part_split& part) {
//   //if (part.deep_features.size() > 0) {
//     in_progress.push_back(part);
//     //return;
//     //}

//     //add_to_filletables(part);

// }

void MainWindow::load_stl() {
  QFileDialog dialog;
  if (dialog.exec()) {
    auto file_names = dialog.selectedFiles();

    if (file_names.size() > 0) {
      auto first = file_names.front();
      std::string fstr = first.toUtf8().constData();
      part_mesh = parse_stl(fstr, 0.0001);

      auto mesh_pd =
	polydata_for_trimesh(part_mesh);
      color_polydata(mesh_pd, 0, 255, 0);
      auto mesh_actor = polydata_actor(mesh_pd);
      
      auto renderers = part_window->GetRenderWindow()->GetRenderers();
      auto renderer = renderers->GetFirstRenderer();
      renderer->AddActor(mesh_actor);
      part_window->show();
      part_window->update();
    }
  }
}

void MainWindow::add_tool() {
  ToolWizard dialog;
  if (dialog.exec()) {
    auto tool = dialog.defined_tool();
    toolset.push_back(tool);

    cout << "Selected tool cut diam = " << tool.cut_diameter() << endl;
    cout << "Number of tools = " << toolset.size() << endl;
  }
}

void MainWindow::define_stock() {
  StockDialog dialog;
  if (dialog.exec()) {
    initial_stock = dialog.defined_stock();
    cout << "SD 1 = " << initial_stock.sides[0] << endl;
    cout << "SD 2 = " << initial_stock.sides[1] << endl;
    cout << "SD 3 = " << initial_stock.sides[2] << endl;
  }
}

void MainWindow::add_parallel() {
  ParallelDialog dialog;
  if (dialog.exec()) {
    auto parallel = dialog.defined_height();
    parallels.push_back(parallel);

    cout << "Selected parallel = " << parallel << endl;
    cout << "Number of parallels = " << parallels.size() << endl;
  }
}

void MainWindow::generate_plan() {
  vice test_vice = custom_jaw_vice(6.0, 1.5, 10.0, point(0.0, 0.0, 0.0));
  //std::vector<plate_height> plates{0.1, 0.3, 0.7};
  fixtures fixes(test_vice, parallels);

  //workpiece workpiece_dims(5.0, 5.0, 5.0, ALUMINUM);

  // tool t1(0.25, 3.0, 4, HSS, FLAT_NOSE);
  // t1.set_cut_diameter(0.25);
  // t1.set_cut_length(0.6);

  // t1.set_shank_diameter(3.0 / 8.0);
  // t1.set_shank_length(0.3);

  // t1.set_holder_diameter(2.5);
  // t1.set_holder_length(3.5);
    
  // tool t2(0.5, 3.0, 4, HSS, FLAT_NOSE);
  // t2.set_cut_diameter(0.5);
  // t2.set_cut_length(0.3);

  // t2.set_shank_diameter(0.5);
  // t2.set_shank_length(0.5);

  // t2.set_holder_diameter(2.5);
  // t2.set_holder_length(3.5);

  // tool t3{0.2334, 3.94, 4, HSS, FLAT_NOSE};
  // t3.set_cut_diameter(0.05);
  // t3.set_cut_length(1.2);

  // t3.set_shank_diameter(0.5);
  // t3.set_shank_length(0.05);

  // t3.set_holder_diameter(2.5);
  // t3.set_holder_length(3.5);

  // // Ridiculous tool used to test feasability
  // tool t4{1.5, 3.94, 4, HSS, FLAT_NOSE};
  // t4.set_cut_diameter(1.5);
  // t4.set_cut_length(2.2);

  // t4.set_shank_diameter(0.5);
  // t4.set_shank_length(0.05);

  // t4.set_holder_diameter(2.5);
  // t4.set_holder_length(3.5);
    
  // vector<tool> tools{t1, t2, t3, t4};

  // string part_path = "/Users/dillon/CppWorkspace/gca/test/stl-files/onshape_parts//Part Studio 1 - Part 1(29).stl";
  // auto mesh = parse_stl(part_path, 0.001);

  box bounding = part_mesh.bounding_box();

  cout << "Bounding box = " << endl;
  cout << bounding << endl;

  fabrication_plan p =
    make_fabrication_plan(part_mesh, fixes, toolset, {initial_stock});

  for (auto& step : p.steps()) {

    auto mesh_pd =
      polydata_for_trimesh(step.arrangement().mesh("part"));
    color_polydata(mesh_pd, 0, 255, 0);
    auto mesh_actor = polydata_actor(mesh_pd);
  
    auto renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(1, 1, 1);
    renderer->AddActor(mesh_actor);

    QVTKWidget* vtk_window = new QVTKWidget(this, Qt::Widget);
    vtk_window->GetRenderWindow()->AddRenderer(renderer);
    vtk_window->show();
    vtk_window->update();
    
    vtk_layout->addWidget(vtk_window);
  }

}

MainWindow::~MainWindow() {
}
