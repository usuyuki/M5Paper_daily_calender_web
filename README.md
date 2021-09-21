# M5Paperで作った卓上カレンダー的なもの

M5Paperという電子ペーパーが使えるマイコンを使って作りました。

**こちらは本体側のソースコードです**

え、、、こんだけかよ、、、ってなると思います。

**本体側では画像を表示しているだけで、ほとんどの処理はサーバー側でPHP,JS,HTML,CSSを用いて行っております**

そして、サーバー側のソースコードはセキュリティ的にどうにもできない状況だったので、公開できてません！！！

下記画像を参考に、心の目でご想像ください。


### 見た目
![IMG20210417174725-1024x768](https://user-images.githubusercontent.com/63891531/134011701-3d5f0f4a-18b6-4c42-b935-1856d2ef98ec.jpg)


### 説明(画面内)
![m5paperInfo-1-1024x768](https://user-images.githubusercontent.com/63891531/134011715-f609b2f0-7d72-4e2f-b963-a25b7969be4c.jpg)


### 説明(インフラ)
![m5paper-1024x580](https://user-images.githubusercontent.com/63891531/134011831-a74ae1cc-2370-4eb4-9edb-3d1fa849ba78.jpg)



## 環境変数について

無線 LAN のパスなどは private.cpp に記載しています(Git では ignore 済み)

private.cpp.example の値を置き換えて./src に配置していただくと動きます。


## ひとりごと

リポジトリ公開化に伴い、セキュリティ上の観点から古いコミットを消すことになったので、記録を残しておく。
![image](https://user-images.githubusercontent.com/63891531/134013557-d7714924-ba4b-4792-8b86-f6cef2273b7c.png)
