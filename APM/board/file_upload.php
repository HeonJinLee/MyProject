<html>
        <head>
                <meta charset="utf-8"/>
        </head>
                <body>
                <form action="test_sh2.php" method="POST" ENCTYPE="multipart/form-data">
                mkdir : <input type="text" name="mkd">
        <input type="submit" value="mkdir"/><br>
                </form>
                </body>
        </head>
</html>

<?php
        echo "mkdir name: ".$_POST['mkd'];
        $res = mkdir($_POST['mkd'],0777);
?> 
