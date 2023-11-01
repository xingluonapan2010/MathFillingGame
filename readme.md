## 基本信息
开发者：@星罗那畔2010  
开发环境：Win11,Visual Studio Community 2022,Win32  
开发简述：有关网格填充的数学逻辑运算小游戏
## 规则简介
一、概念：  
1.点击和触发  
    点击：当用户鼠标按下并在某方块中松开时，该方块被点击。  
    触发：用户对某一个方块进行操作后，响应到的所有方块都叫做被触发，包括被点击的方块自己。  
2.两种状态：  
    true状态：当某一方块被触发的次数为奇数时，该方块为true状态。  
    false状态：当某一方块被触发的次数为偶数时（包括未被触发）时，该方块为false状态。  
3.改变状态：  
    一旦一个方格被触发，则它会改变状态（原false状态的改为true状态，原true状态的改为false状态）  
二、规则：  
    开始时所有方块均为false状态。当用户点击网格中的某一方格时，会触发方块自己和上下左右四个方块，如果未找到，则未找到的方块不被触发。当所有方块均为true状态时，视为成功。
