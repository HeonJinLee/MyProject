<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8"/>
</head>
<body>
<form action="./process.php?mode=insert" method="POST" ENCTYPE="multipart/form-data">
<p>제목 : <input type="text" name="title"></p>
<p>본문 : <textarea name="des" id="" cols="30" rows="10"></textarea></p>
<p>file upload : <input type="file" name="fileUpload" id="fileUpload" size="20"></p>
<p><input type="submit"/></p>
</form>
</body>
</head>
