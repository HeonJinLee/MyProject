<?php
mysql_connect('localhost', 'root', 'asd123');
mysql_select_db('ex31337');
switch($_GET['mode']){
    case 'insert':
        $result = mysql_query("INSERT INTO topic (title, des, created) VALUES ('".mysql_real_escape_string($_POST['title'])."', '".mysql_real_escape_string($_POST['des'])."', now())");
        header("Location: list.php"); 
        break;
    case 'delete':
        mysql_query('DELETE FROM topic WHERE id = '.mysql_real_escape_string($_POST['id']));
        header("Location: list.php"); 
        break;
    case 'modify':
        mysql_query('UPDATE topic SET title = "'.mysql_real_escape_string($_POST['title']).'", des = "'.mysql_real_escape_string($_POST['des']).'" WHERE id = '.mysql_real_escape_string($_POST['id']));
        header("Location: list.php?id={$_POST['id']}");
        break;
}
?>
