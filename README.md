# ogl_mac

### Mac OS创建目录结构：
* Xcode创建新project时候：
    ```
    - src (可重命名，本repo中命名为ogl_mac)
        - src
            - main.cpp
        - src.xcodeproj
    ```
    - 通过在Xcode中创建文件夹来实现proj中文件的目录结构
    - 通过在文件夹中创建文件夹来实现proj中不包含的内容（如download）

* Xcode中设置path（头文件）需要设定全路径，不能是相对路径

### Opengl 配置
- Xcode -> Link Binary With Libraries:
    * libglfw3.a (currently I did not know how to use .dylib, it cannot be included here)
    * CoreVideo.framwork
    * IOKit.framework
    * Cocoa.framework
    * OpenGL.framework
    * GLUT.framework