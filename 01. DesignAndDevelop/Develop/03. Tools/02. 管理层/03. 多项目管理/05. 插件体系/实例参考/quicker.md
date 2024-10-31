甚至可视化编程

这里以一个最简单的程序（单斜杠转化为双斜杠格式）为例，看一下这个动作导出的格式：

本质是一个json存储的节点树，而非代码存储

```json
{
  "LimitSingleInstance": true,
  "SummaryExpression": "$$",
  "SubPrograms": [],
  "Variables": [
    {
      "Key": "context",
      "Type": 0,
      "Desc": "默认的文本变量",
      "DefaultValue": "",
      "SaveState": false,
      "IsInput": false,
      "IsOutput": false,
      "ParamName": null,
      "InputParamInfo": null,
      "OutputParamInfo": null,
      "TableDef": null,
      "CustomType": null
    },
    {
      "Key": "img",
      "Type": 3,
      "Desc": "默认的图片变量",
      "DefaultValue": "",
      "SaveState": false,
      "IsInput": false,
      "IsOutput": false,
      "ParamName": null,
      "InputParamInfo": null,
      "OutputParamInfo": null,
      "TableDef": null,
      "CustomType": null
    },
    {
      "Key": "result",
      "Type": 0,
      "Desc": "插入\\后结果",
      "DefaultValue": "Fail！",
      "SaveState": false,
      "IsInput": false,
      "IsOutput": false,
      "ParamName": null,
      "InputParamInfo": null,
      "OutputParamInfo": null,
      "TableDef": null,
      "CustomType": null
    }
  ],
  "Steps": [
    {
      "StepRunnerKey": "sys:getSelectedText",
      "InputParams": {
        "format": {
          "VarKey": null,
          "Value": "UnicodeText"
        },
        "repeat": {
          "VarKey": null,
          "Value": "2"
        },
        "stopIfFail": {
          "VarKey": null,
          "Value": "1"
        }
      },
      "OutputParams": {
        "output": "context",
        "isSuccess": null
      },
      "IfSteps": null,
      "ElseSteps": null,
      "Note": "",
      "Disabled": false,
      "Collapsed": false,
      "DelayMs": 0
    },
    {
      "StepRunnerKey": "sys:strReplace",
      "InputParams": {
        "type": {
          "VarKey": null,
          "Value": "single"
        },
        "input": {
          "VarKey": "context",
          "Value": null
        },
        "batchReplaceData": {
          "VarKey": null,
          "Value": ""
        },
        "old": {
          "VarKey": null,
          "Value": "\\"
        },
        "new": {
          "VarKey": null,
          "Value": "\\\\"
        },
        "escapeOld": {
          "VarKey": null,
          "Value": "0"
        },
        "replaceEscapes": {
          "VarKey": null,
          "Value": "1"
        },
        "useRegex": {
          "VarKey": null,
          "Value": "0"
        },
        "ignoreCase": {
          "VarKey": null,
          "Value": "0"
        },
        "singleLine": {
          "VarKey": null,
          "Value": "1"
        },
        "multiLine": {
          "VarKey": null,
          "Value": "0"
        }
      },
      "OutputParams": {
        "output": "result"
      },
      "IfSteps": null,
      "ElseSteps": null,
      "Note": "将但斜杠替换为双斜杠，获得可用的路径名",
      "Disabled": false,
      "Collapsed": false,
      "DelayMs": 0
    },
    {
      "StepRunnerKey": "sys:outputText",
      "InputParams": {
        "content": {
          "VarKey": "result",
          "Value": null
        },
        "method": {
          "VarKey": null,
          "Value": "paste"
        },
        "delayBeforePaste": {
          "VarKey": null,
          "Value": "50"
        },
        "delayAfterPaste": {
          "VarKey": null,
          "Value": "10"
        },
        "appendReturn": {
          "VarKey": null,
          "Value": "0"
        }
      },
      "OutputParams": {},
      "IfSteps": null,
      "ElseSteps": null,
      "Note": "将处理完成的文本输入到当前光标处",
      "Disabled": false,
      "Collapsed": false,
      "DelayMs": 0
    }
  ]
}
```