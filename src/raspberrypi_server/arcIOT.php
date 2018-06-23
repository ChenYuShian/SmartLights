<?php
	echo $_GET[color];
	$str=str_replace("_"," ",$_GET[color]);
	echo "  ";
	echo $str;
	echo exec("./arcIOT '$str'");
?>
