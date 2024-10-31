## 原生QML的麻烦之处

在QML文档上直接上样式是有点麻烦的，而且如果你本身就比较熟悉CSS，那么用CSS样式无疑更好

例如：实现单边边框在QML中是麻烦的，参考：https://codeantenna.com/a/KYFKNlv9CA

```js
Rectangle {
    width: window.width
    height: 70
    border.color: "#cdcdcd"
}
```

方法1

```js
Page {
    id: page
    x: 200
    y: 78
    width: 200
    height: 200

    background: Rectangle {
        anchors.fill: parent
        color: "white"
        border.width: 1
        border.color: "black"

        // 使用矩形覆盖上层Rectangle的边框
        Rectangle {
            color: parent.color
            border.width: 0
            anchors.fill: parent
            // 使用Margin来确定是否显示边框
            anchors.leftMargin: 1
            anchors.topMargin: 1
            anchors.rightMargin: 1
            anchors.bottomMargin: 0
        }
    }
}
```

方法二：使用Shape绘制边框线

```js
Page {
    id: pageID
    x: 200
    y: 78
    width: 200
    height: 200

    background: Rectangle {
        anchors.fill: parent
        color: "white"
        border.width: 0
        border.color: "black"
        // 绘制一条边框
        Shape {
            anchors.fill: parent
            ShapePath {
                strokeWidth: 0
                strokeColor: "black"
                strokeStyle: ShapePath.SolidLine
                startX: 0
                startY: 0
                PathLine {
                    x: pageID.width
                    y: 0
                }
                PathLine {
                    x: pageID.width
                    y: pageID.height
                }
            }
        }
    }
}
```



## CSS？？？

好像不支持



## QSS样式？

Qt Style Sheets 不确定QML能不能用