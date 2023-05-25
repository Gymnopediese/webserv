<!DOCTYPE html>
<html>
<head>
  <title>Hello, World!</title>
</head>
<body>
  <?php
    echo $_POST['username'];
	echo "|";
	echo $_POST['password'];
	echo "|";
	echo $_COOKIE['TOKEN'];
	echo "|";
	echo $_COOKIE['Token'];
  ?>
</body>
</html>