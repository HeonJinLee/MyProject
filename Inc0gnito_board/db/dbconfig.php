<?php
   $db = new mysqli('localhost', 'root', 'moo1gogg1', 'board');

   if($db->connect_error) {
      die('�����ͺ��̽� ���ῡ ������ �ֽ��ϴ�.\n�����ڿ��� ���� �ٶ��ϴ�.');
   }

   $db->set_charset('utf8');
?>