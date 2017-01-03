<?php
	echo $_POST['filename'];
        $content = "./db -showContent ".$_POST['filename'];;
        echo $content;
        exec("$content",$output);
        print_r($output);
        $myfile = fopen("dataBaseFile", "w") or die("Unable to open file!");
        foreach ($output as $line){
                fwrite($myfile,$line."\n");
        }
        fclose($myfile);
?>

