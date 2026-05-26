# 低电量保护功能实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 当电池电压低于3300mV时，自动执行趴下动作、显示睡眠表情，并在OLED上显示电池图标提示充电。

**Architecture:** 在主循环中检查电池电压，低电量时强制覆盖动作和表情，忽略语音指令。修改FaceConfig.c添加低电量保护逻辑，添加电池图标数据。

**Tech Stack:** STM32F103, Keil MDK, C语言

---

## 文件结构

**修改的文件：**
- `Hardware/OLED_Data.c` — 添加电池图标数据
- `Hardware/OLED_Data.h` — 声明电池图标
- `Hardware/FaceConfig.c` — 添加低电量保护逻辑
- `Hardware/main.c` — 添加低电量状态下的动作控制

---

### Task 1: 添加电池图标数据

**Files:**
- Modify: `Hardware/OLED_Data.c`
- Modify: `Hardware/OLED_Data.h`

- [ ] **Step 1: 在 OLED_Data.c 中添加电池图标数据**

在 `Face_very_happy` 图标数据之后添加：

```c
/*电池图标数据 - 16x8像素*/
const uint8_t Battery_Icon[] = {
    0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF,  // 电池轮廓
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00   // 电池内部（可填充）
};
```

- [ ] **Step 2: 在 OLED_Data.h 中声明电池图标**

在 `extern const uint8_t Face_very_happy[];` 之后添加：

```c
extern const uint8_t Battery_Icon[];
```

- [ ] **Step 3: 提交更改**

```bash
git add Hardware/OLED_Data.c Hardware/OLED_Data.h
git commit -m "feat: add battery icon data for low battery protection"
```

---

### Task 2: 修改 FaceConfig.c 添加低电量保护逻辑

**Files:**
- Modify: `Hardware/FaceConfig.c`

- [ ] **Step 1: 添加低电量检查逻辑**

在 `Face_Config` 函数的 `switch(FaceMode)` 之前添加低电量检查：

```c
void Face_Config(void)
{
    /*低电量保护检查*/
    if(Average_Battery < 3300 && Average_Battery > 0)
    {
        /*强制睡眠表情*/
        OLED_Clear();
        OLED_ShowImage(0, 0, 128, 64, Face_sleep);
        
        /*显示电池图标和电压值*/
        OLED_ShowImage(112, 0, 16, 8, Battery_Icon);  // 右上角显示电池图标
        OLED_ShowString(0, 56, "Low Battery!", OLED_6X8);  // 底部显示提示
        OLED_ShowFloatNum(80, 56, Average_Battery / 1000.0, 1, 1, OLED_6X8);  // 显示电压
        OLED_ShowString(108, 56, "V", OLED_6X8);
        
        OLED_Update();
        return;  // 直接返回，不执行后续逻辑
    }
    
    /*原有逻辑*/
    switch(FaceMode)
    {
        // ... 原有代码 ...
    }
    
    /*电量处理*/
    if(Battery_Bit)
    {
        // ... 原有代码 ...
    }
    
    OLED_Update();
}
```

- [ ] **Step 2: 提交更改**

```bash
git add Hardware/FaceConfig.c
git commit -m "feat: add low battery protection in FaceConfig"
```

---

### Task 3: 修改 main.c 添加低电量动作控制

**Files:**
- Modify: `User/main.c`

- [ ] **Step 1: 添加低电量动作控制**

在主循环中添加低电量检查，强制趴下动作：

```c
while(1)
{
    /*低电量保护检查*/
    if(Average_Battery < 3300 && Average_Battery > 0)
    {
        ActionMode = MODE_LIE_DOWN;  // 强制趴下
        FaceMode = FACE_SLEEP;       // 强制睡眠表情
    }
    
    Face_Config();
    PetAction_Perform();
}
```

- [ ] **Step 2: 提交更改**

```bash
git add User/main.c
git commit -m "feat: add low battery action control in main loop"
```

---

### Task 4: 验证和调试

- [ ] **Step 1: 编译项目**

在Keil MDK中编译项目，确保没有编译错误。

- [ ] **Step 2: 测试低电量保护功能**

1. 使用可调电源模拟低电压（3.2V）
2. 验证是否自动趴下+显示睡眠表情+电池图标
3. 调高电压至3.4V，验证是否恢复正常行为
4. 验证低电量状态下语音指令是否被忽略

- [ ] **Step 3: 验证OLED显示**

1. 检查电池图标位置是否正确（右上角）
2. 检查电压值显示精度（0.1V）
3. 检查"Low Battery!"提示文字位置

- [ ] **Step 4: 最终提交**

```bash
git add -A
git commit -m "feat: complete low battery protection feature"
```

---

## 验证清单

- [ ] 电池图标数据已添加
- [ ] FaceConfig.c 低电量保护逻辑已实现
- [ ] main.c 低电量动作控制已实现
- [ ] 低电量时自动趴下+睡眠表情+电池图标显示
- [ ] 电量恢复正常后自动恢复行为
- [ ] 低电量状态下语音指令被忽略
- [ ] 编译无错误
- [ ] 功能测试通过
