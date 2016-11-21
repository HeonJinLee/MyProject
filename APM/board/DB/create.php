<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8"/>
	<title>join</title>
	<style type="text/css">
	.align{text-align:center}
	</style>
</head>
<body>
<div class="align">
<h1>회원가입</h1>
<hr>
<form action="./join_db.php" method="POST">
<p>ID:<input type="text" name="join_id"/></p>
<p>PW:<input type="password" name="join_pw"/></p>
<p>NAME:<input type="text" name="join_name"/></p>
<input type="submit" value="가입"/>
</form>
<a href="../login.php">
<input type="submit" value="취소" name="join_exit"/></a>
</div>
</body>
</html>	
