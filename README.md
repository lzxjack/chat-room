## 1. 注册 GET

### 发送

```
http://47.110.144.145:4567/register?name=jack&pwd=123456
```

### 返回

成功：

```
{
    "register": "0"
}
```

失败：

```
{
	"register": "-1"
	"error": "0,1,2,3"
}
```

0：用户名已存在

1：用户名不符合规范

2：密码不符合规范

3：其他

## 2. 登录 GET

### 发送

```
http://47.110.144.145:4567/login?name=jack&pwd=123456
```

### 返回

成功：

```
{
    "login": "0",
    "token": "xxxxxxxxxxxxx"
}
```

失败：

```
{
    "login": "-1"
    "error": "0,1,2"
}
```

0：用户名不存在

1：密码不匹配

2：其他

## 3. 获取消息 GET

### 发送

```
http://47.110.144.145:4567/information?name=xxx
```
### 返回  

成功：

  ```
{
	"information": "0",
	"msg": [{},{},{}...]
}
  ```
  无新信息：
  ```
{
	"information": "-1",
	"msg": []
}
  ```
## 4. 发送消息 POST

### 发送

```
http://47.110.144.145:4567/information?msg=xxxx&name=xxx&time=xxxxxx&id=xxxxxxx
```

### 返回

```
{
	"msg": "0"
}
```

