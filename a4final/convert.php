<?php	
	$test = "./a4 " ."files/".$_POST['filename'];
        echo $test;
        exec("$test",$out);
        print_r($out);
?>

