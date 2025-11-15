//
//  main.mm
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/13.
//

#include "Window.hpp"

int main(int argc, const char * argv[]) {
    Window window;
    
    window.init();
    window.run();
    window.release();
    
    return 0;
}
