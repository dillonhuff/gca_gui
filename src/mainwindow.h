#ifndef mainwindow_h
#define mainwindow_h

#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <QMainWindow>
#include <QScopedPointer>
#include <QVTKWidget.h>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialog>

#include "backend/tool.h"
#include "geometry/plane.h"
#include "geometry/mesh_operations.h"
#include "geometry/triangular_mesh.h"
#include "utils/arena_allocator.h"

//#include "part_slicing.h"

class AddToolDialog : public QDialog {
public:
  AddToolDialog() {
    
  }

  gca::tool defined_tool() const {
    gca::tool t4{1.5, 3.94, 4, gca::HSS, gca::FLAT_NOSE};
    t4.set_cut_diameter(1.5);
    t4.set_cut_length(2.2);

    t4.set_shank_diameter(0.5);
    t4.set_shank_length(0.05);

    t4.set_holder_diameter(2.5);
    t4.set_holder_length(3.5);

    return t4;
  }

private slots:
private:
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    virtual ~MainWindow();

private slots:
  void generate_plan();
  void load_stl();
  void add_tool();

  // void handle_accept();
  // void handle_reject();
  // void handle_set_done();

private:

  gca::arena_allocator alloc;
  // vtkSmartPointer<vtkRenderer> renderer;
  // vtkSmartPointer<vtkActor> active_plane_actor;
  // vtkSmartPointer<vtkActor> active_mesh_actor;
  // vtkSmartPointer<vtkActor> active_fillet_actor;
  // vtkSmartPointer<vtkPolyData> active_mesh_polydata;

  // std::vector<gca::plane> slice_planes;
  // gca::plane active_plane;
  // gca::triangular_mesh active_mesh;

  // std::vector<gca::part_split> in_progress;

  // active_fillet active_fillet_part;
  // int active_fillet_group_index, active_fillet_index;
  // std::vector<filletable_part> in_progress_fillets;
  // std::vector<filletable_part> finished_fillets;

  // QLabel* in_progress_heading;


  gca::triangular_mesh part_mesh;
  std::vector<gca::tool> toolset;
    
  QPushButton* add_tool_button;
  QPushButton* define_vice_button;
  QPushButton* add_parallel_button;
  QPushButton* define_stock_button;
  QPushButton* generate_plan_button;

  QVTKWidget* part_window;
  QVBoxLayout *main_part_layout;
  QVBoxLayout *vtk_layout;

  // void update_active_mesh(const gca::triangular_mesh& m);
  // void update_active_plane(const gca::plane p);
  // void clear_active_plane();
  // void clear_active_mesh();
  // void clear_active_fillet();

  // void slice_next_part();

  // // Commands for slice mode
  // void handle_accept_slice();
  // void handle_reject_slice();
  // void handle_set_done_slice();

  // void add_to_queues(const gca::part_split& part);

  // void add_to_filletables(const gca::part_split& part);

  // // Commands for fillet mode
  // void handle_accept_fillet();
  // void handle_reject_fillet();
  // void handle_set_done_fillet();

  // void switch_to_fillet_mode();
  // void fillet_next_part();
  // void set_active_fillet(const active_fillet& af);
  // void fillet_next();

  //   // void set_active_fillet(const gca::triangular_mesh& part,
  //   // 			 const std::vector<gca::shared_edge>& fillet);

  // active_fillet next_active_fillet();

  // // Commands for complete mode
  // void set_complete_mode();
  
};

#endif
