<?php
        $testA3 = "./a4 " ."files/".$_POST['filename'];
        exec("$testA3",$a3out);
	echo $testA3;
	print_r($a3out);
	$test = "./db " ."files/".$_POST['filename'].".html";
        exec("$test",$out);
	unlink("files/".$_POST['filename'].".html");
	echo $test;
        print_r($out);
	$withExt = $_POST['filename'];
	$withoutExt = preg_replace('/\\.[^.\\s]{3,4}$/', '', $withExt);
	$content = "./db -showContent " .$withoutExt;
	echo $content;	
	exec("$content",$output);
	print_r($output);
	$myfile = fopen("dataBaseFile", "w") or die("Unable to open file!");
	foreach ($output as $line){
		fwrite($myfile,$line."\n");
	}
	fclose($myfile);
?>

