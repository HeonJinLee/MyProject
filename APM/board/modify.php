<?php
mysql_connect('localhost', 'root', 'asd123');
mysql_select_db('ex31337');
$result = mysql_query('SELECT * FROM topic WHERE id = '.mysql_real_escape_string($_GET['id']));
$topic = mysql_fetch_array($result);
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8"/>
    </head>   
    <body>
        <form action="./process.php?mode=modify" method="POST">
            <input type="hidden" name="id" value="<?=$topic['id']?>" />
            <p>제목 : <input type="text" name="title" value="<?=htmlspecialchars($topic['title'])?>"></p>
            <p>본문 : <textarea name="des" id="" cols="30" rows="10"><?=htmlspecialchars($topic['des'])?></textarea></p>
            <p><input type="submit" /></p>
        </form>
    </body>
</html>
