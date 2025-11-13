# STM32F103C8T6 VSCode + ARM GCC + DapLink 开发环境模板

此项目提供一个使用 VSCode、ARM GCC 工具链和 OpenOCD 进行 STM32F103C8T6 微控制器开发的完整环境模板。项目基于 STM32CubeMX 生成的 HAL 库代码，并使用 CMake 进行构建管理，旨在为开发者提供一个开箱即用的开发、编译、烧录和调试环境。

## 项目结构

```
stm32f103c8t6_vscode_armgcc_DapLink_env_tmp/
├── Core/                 # STM32CubeMX 生成的核心代码 (HAL, MSP, 中断处理等)
├── Drivers/              # STM32 HAL 库和 CMSIS 库文件
├── user/                 # 用户代码目录
│   ├── Application/      # 用户应用程序代码
│   └── Peripherals/      # 用户外设驱动代码
├── .vscode/              # VSCode 配置 (tasks.json, launch.json)
├── cmake/                # CMake 工具链和构建配置
├── CMakeLists.txt        # 项目主 CMake 配置文件
├── startup_stm32f103xb.s # 启动文件
├── STM32F103XX_FLASH.ld  # 链接脚本
└── ...
```

## 环境要求

- **操作系统**: Windows, Linux, 或 macOS
- **IDE**: [Visual Studio Code](https://code.visualstudio.com/)
- **编译器**: [ARM GNU Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm) (arm-none-eabi-gcc)
- **烧录/调试**: [OpenOCD](https://openocd.org/) (支持 CMSIS-DAP, ST-Link, J-Link 等调试器)
- **构建系统**: [CMake](https://cmake.org/) (版本 >= 3.22)
- **Make 工具**: Windows 用户推荐安装 [MinGW-w64](https://www.mingw-w64.org/) 或使用 Windows Subsystem for Linux (WSL)

## 扩展插件 (VSCode)

安装以下 VSCode 扩展以获得最佳开发体验：

- C/C++ (Microsoft)
- Cortex-Debug (marus25)
- CMake Tools (Kitware)
- ARM (Dan<Dan>

## 配置说明

### 1. 工具路径配置

编辑 `.vscode/tasks.json` 和 `.vscode/launch.json` 文件，将其中的工具路径修改为你的本地安装路径：

**tasks.json**:
```json
{
  "label": "Flash STM32",
  "command": "D:/software/openocd-0.12.0-7/bin/openocd.exe", // 修改为你的 OpenOCD 安装路径
  "args": [
    "-s", "D:/software/openocd-0.12.0-7/openocd/scripts"    // 修改为你的 OpenOCD 脚本目录
  ]
}
```

**launch.json**:
```json
{
  "serverpath": "D:/software/openocd-0.12.0-7/bin/openocd.exe",  // 修改为你的 OpenOCD 路径
  "searchDir": [
    "D:/software/openocd-0.12.0-7/openocd/scripts"               // 修改为你的 OpenOCD 脚本目录
  ],
  "gdbPath": "D:/software/armgcc/bin/arm-none-eabi-gdb.exe"      // 修改为你的 GDB 路径
}
```

### 2. 调试器配置

根据你使用的调试器类型，修改 `.vscode/tasks.json` 和 `.vscode/launch.json` 中的 OpenOCD 配置文件：

- **CMSIS-DAP**: `interface/cmsis-dap.cfg`
- **ST-Link**: `interface/stlink.cfg` 或 `interface/stlink-v2.cfg`
- **J-Link**: `interface/jlink.cfg`

同时根据目标芯片修改目标配置文件 (如 `target/stm32f1x.cfg` 适用于 STM32F1 系列)。

## 构建项目

### 使用 VSCode Tasks

1. 打开命令面板 (`Ctrl+Shift+P`)
2. 输入 "Tasks: Run Task"
3. 选择以下任务之一：
   - `CMake Configure`: 配置 CMake 项目
   - `Build Project`: 编译项目
   - `Clean Build`: 清理构建目录
   - `Build & Flash`: 编译并烧录
   - `Rebuild & Flash`: 清理、编译并烧录

### 配置快捷键 (例如 CTRL+F5)

为了提高开发效率，你可以将常用任务（如 `Build & Flash`）绑定到快捷键上。VS Code 默认将 F5 用于启动调试，而 Ctrl+F5 在某些语言中是"运行不调试"。我们可以覆盖它来执行构建和烧录任务。

有两种方法可以实现：

**方法一：通过图形界面设置**

1. 打开 VSCode 快捷键设置：
   - Windows/Linux: `Ctrl+K Ctrl+S`
   - macOS: `Cmd+K Cmd+S`
   - 或通过菜单 `文件` -> `首选项` -> `键盘快捷方式`
2. 在搜索框中输入 "Tasks: Run Task"。
3. 找到 "Tasks: Run Task" 命令，点击其左侧的 `+` 号或 "设置键绑定" 按钮。
4. 按下你想要设置的快捷键组合，例如 `Ctrl+F5`。
5. 在弹出的命令列表中，选择 `Build & Flash` 任务。
6. 现在你可以通过 `Ctrl+F5` (或你设置的其他快捷键) 直接执行编译并烧录操作。

**方法二：直接编辑 keybindings.json**

1. 按 `Ctrl+Shift+P` → 输入 "Preferences: Open Keyboard Shortcuts (JSON)"
2. 在打开的 `keybindings.json` 文件中添加以下配置：
   ```json
   [
     {
       "key": "ctrl+f5",
       "command": "workbench.action.tasks.runTask",
       "args": "Build & Flash",
       "when": "editorTextFocus"
     }
   ]
   ```
3. 保存文件后，只要在编辑器中，按 `Ctrl+F5` 就会运行 "Build & Flash" 任务。

### 手动构建

```bash
# 创建并进入构建目录
mkdir build
cd build

# 配置项目 (Windows 使用 "MinGW Makefiles")
cmake -G "MinGW Makefiles" ..

# 编译项目
make -j15  # -j 参数可加快编译速度
```

## 烧录固件

### 使用 OpenOCD (命令行)

```bash
# 确保已进入 build 目录
cd build

# 烧录生成的 HEX 文件
openocd -f interface/your_interface.cfg -f target/stm32f1x.cfg -c "program test.hex verify reset exit"
```

### 使用 VSCode Tasks

运行 VSCode Task "Flash STM32"。

## 调试

1. 在 VSCode 中打开项目
2. 确保 `.vscode/launch.json` 配置正确
3. 设置断点
4. 按 `F5` 或点击 "Run and Debug" 按钮启动调试会话

## 项目特点

- **CMake 构建系统**: 提供灵活、可移植的构建方式
- **VSCode 集成**: 完整的开发、编译、烧录、调试流程
- **用户代码分离**: `user/` 目录下组织用户代码，便于管理和维护
- **多语言支持**: 支持 C 和 C++ 混合编程
- **自动文件收集**: CMakeLists.txt 自动收集 `user/` 目录下的源文件

## 用户代码开发

用户应用程序应放在 `user/Application/` 目录下。项目模板在 `user/Application/src/user_main.cpp` 中提供了一个简单的 LED 控制示例，主循环会调用此函数。你可以在此基础上扩展你的应用逻辑。

## 许可证

请参阅项目根目录下的 `LICENSE` 文件。
