//
//  main.mm
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/13.
//

#include "Window.hpp"
#include "Model.hpp"

int main(int argc, const char * argv[]) {
    Model *model = new Model("sphere.glb");
    
    Window window;
    
    window.run();
    window.release();
    
    return 0;
}
