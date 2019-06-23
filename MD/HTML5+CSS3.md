## HTML5基本语法



```html
<!DOCTYPE html>		//指定文档格式为html,不区分大小写
<meta charset="UTF-8">	//指定字符编码格式
<script type="text/javascript" src="scriptfile.js"></script>
//script标签  type可以省略
```

## 引入CSS文件

```html
<link rel="stylesheet" type="text/css" href="stylefile.css">
//引入外部CSS文件 href是CSS文件地址,其余两项默认值  type可省略
```

```html
<style type = "text/css">
body{
    
}
h1{
    
}
<style>
    //引入外部CSS文件 type不可省略
```

## CSS选择器

- 基本选择器

| 序号 | 选择器  | 含义                                           |
| ---- | ------- | ---------------------------------------------- |
| 1    | *       | 通用元素选择器，匹配任何元素                   |
| 2    | E       | 标签选择器，匹配所有使用E标签的元素            |
| 3    | .info   | class选择器，匹配所有class属性中包含info的元素 |
| 4    | #footer | id选择器，匹配所有id属性等于footer的元素       |

```html
* { margin:0; padding:0; }

p { font-size:2em; }

.info { background:#ff0; }

p.info { background:#ff0; }

p.info.error { color:#900; font-weight:bold; }

#info { background:#ff0; }

p#info { background:#ff0; }
```

