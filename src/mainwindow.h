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
#include <QWizard>
#include <QLineEdit>

#include "geometry/plane.h"
#include "geometry/mesh_operations.h"
#include "geometry/triangular_mesh.h"
#include "synthesis/fixture_analysis.h"
#include "utils/arena_allocator.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    virtual ~MainWindow();

private slots:
  void generate_plan();
  void load_stl();
  void add_tool();
  void add_parallel();
  void define_stock();

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
  std::vector<gca::plate_height> parallels;
  gca::workpiece initial_stock;
  gca::vice test_vice;
    
  QPushButton* add_tool_button;
  QPushButton* define_vice_button;
  QPushButton* add_parallel_button;
  QPushButton* define_stock_button;
  QPushButton* generate_plan_button;

  QVTKWidget* part_window;
  QVBoxLayout *main_part_layout;
  QVBoxLayout *vtk_layout;

  
};

#endif
