<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8"/>
	<title>login</title>
	<style type="text/css">
	.align{text-align:center}
	</style>
</head>
<body>
<div class="align">
<form action="./db/login_db.php" method="POST">
<h1>환영합니다</h1>
<hr>
<p>ID : <input type="text" name="login_id"></p>
<p>PW : <input type="password" name="login_pw"></p>
</br>
<p><input type="submit" value="로그인"/>
</form>
<a href="./db/create.php">
<input type="submit" value="회원가입"/></p>
</div>
</body>
</html>
