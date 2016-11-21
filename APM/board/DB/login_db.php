<?php
mysql_connect('localhost','root','asd123');
mysql_select_db('ex31337');

$id = $_POST['login_id'];
$pass = $_POST['login_pw'];

$getId = "select id from people where id='$id'";
$getId = mysql_query($getId);
$getId = mysql_fetch_array($getId);

if($getId['id'])
{
	$getPass = "select pw from people where id='$id'";
	$getPass = mysql_query($getPass);
	$getPass = mysql_result($getPass,0);
	
	if($getPass === $pass){
	$key = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789^/"';
	for($i=0;$i<=63;$i++)
		$token=$key[rand(0,63)];

	$updateToken="update people set token='$token' where id='$id'";
 	$updateToken=mysql_query($updateToken);

	$_SESSION['token'] = $token;
	
	header("Location: ../list.php");
	
	return 0;
}
else {
	echo "PASSWORD ERROR";
	return 1;
	}
}
else{
	echo "ID ERROR";
	return 1;
}
?>

