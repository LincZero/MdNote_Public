# 杂项

## demo

```python
class MyNode:
    def __init__(self):
        pass
    
    @classmethod
    def INPUT_TYPES(s):
        return {
            "required": {
            
            
            },
        }
 
    RETURN_TYPES = ()
    RETURN_NAMES = ()
 
    FUNCTION = "test"
 
    #OUTPUT_NODE = False
 
    CATEGORY = "image/mynode2"
 
    def test(self):
        return ()
 
 
# 包含要导出的所有节点及其名称的字典
# NOTE: 名称应该是全局唯一的
NODE_CLASS_MAPPINGS = {
    "MyNode": MyNode
}
 
# 包含节点的友好/人类可读标题的字典
NODE_DISPLAY_NAME_MAPPINGS = {
    "FirstNode": "My First Node"
}
```


```python
class NodeKO:
    def __init__(self):
        pass
    
    @classmethod
    def INPUT_TYPES(s):
    return {
            "required": {
                "text": ("STRING", {"default":"Hey Hey!"}),
                "text2": ("STRING", {"forceInput" True}),               
            },
        }
 
    RETURN_TYPES = ("STRING","INT", "FLOAT", 'LATENT', "CONDITIONING", "IMAGE", "MODEL")
    RETURN_NAMES = ("TxtO", "IntO", "FloatO", "Latent output. Really cool, huh?", "A condition" , "Our image." , "Mo mo modell!!!")
 
    FUNCTION = "test"
 
    #OUTPUT_NODE = False
 
    CATEGORY = "nodeKO"
 
    def test(self):
        return ()
 
 
# A dictionary that contains all nodes you want to export with their names
# NOTE: names should be globally unique
NODE_CLASS_MAPPINGS = {
    "My KO Node": MyNode
}
 
# A dictionary that contains the friendly/humanly readable titles for the nodes
NODE_DISPLAY_NAME_MAPPINGS = {
    "FirstNode": "My First Node"
}
```

