<?php
mysql_connect("localhost","root","asd123");
mysql_select_db("ex31337");

$result=mysql_query("insert into people (id, pw, name) values ('".$_POST['join_id']."','".$_POST['join_pw']."','".$_POST['join_name']."')");

header("Location: ../login.php");
?>
