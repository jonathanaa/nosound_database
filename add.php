<!DOCTYPE html>
<head>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha/css/bootstrap.min.css">
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha/js/bootstrap.min.js"></script>
<link rel="stylesheet" href="css/bootstrap.min.css">
<script src="js/bootstrap.min.js"></script>
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.8.0/jquery.min.js">
</script>
</head>
<body>
<div class="container">
<?php
header("Content-Type:text/html; charset=utf-8");

$url=$_POST[url];
$title=$_POST[title];
$content=$_POST[content];
$viewcount=$_POST[viewcount];
$res=$_POST[res];
$duration=$_POST[duration];

//用_取代空白，不然python會有問題
$url=str_replace(" ","_",$url);
$title=str_replace(" ","_",$title);
$content=str_replace(" ","_",$content);
$viewcount=str_replace(" ","_",$viewcount);
$res=str_replace(" ","_",$res);
$duration=str_replace(" ","_",$duration);

$path="python add.py "; //需要注意的是：末尾要加一個空格
passthru($path.$url." ".$title." ".$content." ".$viewcount." ".$res." ".$duration);//等同於命令`python python.py 引數`，並接收列印出來的資訊
//用js做按鈕返回首頁
echo '<script type="text/javascript">';
echo 'function backtohome() {';
echo 'window.location.href="http://localhost/nosound_database/interface/home.html";';
echo '}';
echo '</script>';
echo "<br>";
echo '<button class="btn btn-warning btn-lg btn-block" onclick="backtohome()">返回首頁</button>';
//----------------------------------
?>
</div></body></html>