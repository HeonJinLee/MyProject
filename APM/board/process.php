<?php
mysql_connect('localhost', 'root', 'asd123');
mysql_select_db('sid31337');
switch($_GET['mode']){
    case 'insert':
        $result = mysql_query("INSERT INTO board (title, des, created) VALUES ('".$_POST['title']."', '".$_POST['des']."', now())");
	

	$target_dir = "uploads/";
	$target_file = $target_dir . basename($_FILES["fileUpload"]["name"]);
	$uploadOk = 1;

	if (file_exists($target_file)) {
	    echo "Sorry, file already exists.";
 	   $uploadOk = 0;
    }

    if ($_FILES["fileUpload"]["size"] > 500000) {
        echo "Sorry, your file is too large.";
        $uploadOk = 0;
    }
		
	$imageFileType = pathinfo($target_file,PATHINFO_EXTENSION);
if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg" && $imageFileType !="gif"){
	echo "Sorry, only JPG, JPEG, PNG , GIF files are allowed.";
	$uploadOk = 0;
}

    if ($uploadOk == 0) {
       echo "Sorry, your file was not uploaded.";
    // if everything is ok, try to upload file
    } else {
        if (move_uploaded_file($_FILES["fileUpload"]["tmp_name"], $target_file)) {
        echo "The file ". basename( $_FILES["fileUpload"]["name"]). " has been uploaded.";
    } else {
        echo "Sorry, there was an error uploading your file.";
    }
}
        header("Location: list.php"); 
        break;

    case 'delete':
        mysql_query('DELETE FROM board WHERE id = '.$_POST['id']);
        header("Location: list.php"); 
        break;

    case 'modify':
        mysql_query('UPDATE board SET title = "'.$_POST['title'].'", des = "'.$_POST['des'].'" WHERE id = '.$_POST['id']);
        header("Location: list.php?id={$_POST['id']}");
        break;
}
?>
