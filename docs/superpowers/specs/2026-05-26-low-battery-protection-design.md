# 低电量保护功能设计文档

## 项目背景
基于STM32F103的桌面宠物狗项目，现有电源检测模块（PowerDetect）通过ADC采集电池电压，每20ms采样一次并计算平均值。需要新增低电量保护功能：当电池电压低于阈值时，自动执行趴下动作、显示睡眠表情，并在OLED上显示电池图标提示充电。

## 目标
- 当 `Average_Battery < 3300mV` 时，强制执行趴下+睡眠表情
- 在OLED上显示电池图标和电压值
- 低电量状态下忽略语音指令
- 电量恢复后自动恢复正常行为

## 现有代码分析

### 电源检测模块（PowerDetect.c）
- `PowerDetect_Init()` — 初始化TIM3定时器，配置20ms中断
- `GetBattery()` — 读取ADC值并转换为电压（mV）
- `GetAverage_Battery()` — 计算100次采样的平均值，存储在 `Average_Battery`

### 全局变量（Variable.h）
- `Average_Battery` — 电池平均电压（mV）
- `ActionMode` — 动作模式枚举（MODE_LIE_DOWN为趴下）
- `FaceMode` — 表情模式枚举（FACE_SLEEP为睡眠）

### 主程序（main.c）
- 主循环执行 `Face_Config()` 和 `PetAction_Perform()`
- TIM3中断每20ms调用 `GetAverage_Battery()`

## 设计方案

### 方案选择
**主循环检查方案** — 在主循环中检查电池电压，低电量时强制覆盖动作和表情。

选择理由：
1. 项目结构简单，不需要复杂的状态机
2. 20ms的电池采样间隔已经足够及时
3. 代码改动最小，与现有架构一致

### 数据流
```
TIM3中断(20ms) → GetAverage_Battery() → 更新Average_Battery
                                          ↓
主循环 → 检查Average_Battery < 3300? → 是 → 强制趴下+睡眠+显示电池图标
                                → 否 → 正常执行语音指令
```

### 修改文件

#### 1. main.c
在主循环中添加低电量检查逻辑：

```c
while(1)
{
    if(Average_Battery < 3300)  // 低电量保护
    {
        ActionMode = MODE_LIE_DOWN;  // 强制趴下
        FaceMode = FACE_SLEEP;       // 睡眠表情
        OLED_Clear();
        OLED_ShowImage(0, 0, 128, 64, Face_sleep);  // 显示睡眠表情
        OLED_ShowBatteryIcon(Average_Battery);       // 显示电池图标+电压
        OLED_Update();
    }
    else
    {
        Face_Config();        // 正常表情配置
        PetAction_Perform();  // 正常动作执行
    }
}
```

#### 2. OLED_Data.h/c
添加电池图标数据：
- 电池轮廓图标（16x8像素或类似）
- 电量填充图标（多级）

#### 3. OLED.h/c
添加显示电池图标函数：
```c
void OLED_ShowBatteryIcon(uint16_t voltage);
```
功能：
- 在OLED右上角显示电池轮廓
- 根据电压值显示填充程度
- 在电池图标下方显示电压值（如 "3.2V"）

### 低电量阈值
- 阈值：3300mV（3.3V）
- 适用于单节锂电池（3.7V标称），约10%电量

### 行为规范
1. **低电量状态**：
   - 强制 `ActionMode = MODE_LIE_DOWN`
   - 强制 `FaceMode = FACE_SLEEP`
   - 忽略语音指令
   - 显示睡眠表情+电池图标+电压值

2. **电量恢复**：
   - 当 `Average_Battery >= 3300` 时自动恢复
   - 恢复正常语音控制和表情显示

3. **边界条件**：
   - 首次上电时如果电量低，立即进入保护状态
   - 电压值显示精度：0.1V

## 验证方法
1. 使用可调电源模拟低电压（3.2V），验证是否自动趴下+显示睡眠表情+电池图标
2. 调高电压至3.4V，验证是否恢复正常行为
3. 验证低电量状态下语音指令是否被忽略
4. 验证OLED显示是否正确（电池图标位置、电压值精度）
