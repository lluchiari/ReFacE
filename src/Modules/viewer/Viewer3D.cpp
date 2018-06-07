#include <Modules/viewer/Viewer3D.h>

Viewer3D::Viewer3D(){

}

Viewer3D::~Viewer3D(){

}

int Viewer3D::config(string){
    if(LOG_VIEWER_3D){cout << "Viewer3D::config(): Start...\n";}
    if(LOG_VIEWER_3D){cout << "Viewer3D::config(): Finish_OK!\n";}
    return 1;
}

int Viewer3D::run(){
    if(LOG_VIEWER_3D){cout << "Viewer3D::run(): Start...\n";}
    if(LOG_VIEWER_3D){cout << "Viewer3D::run(): Finish_OK!\n";}
    return 1;
}

