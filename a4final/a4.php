<!DOCTYPE html>
<html>
<head>
	<title>Mathieu's A4</title>
<!-- Latest compiled and minified CSS -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">

<!-- jQuery library -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>

<!-- Latest compiled JavaScript -->
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
<script src="jquery-js.js"></script>

<link rel="stylesheet" type="text/css" href="mystyle.css">
</head>
<body>
<?php
        exec("./db -lines",$out);
?>
<div class="site-description">
	<h1>Hello World</h1>
<span class="intro">Welcome to my CIS*2750 A4, on this web page you will be able to upload and convert your text files to html files. Enjoy!</span>
</div>
<input type="hidden" id="refreshed" value="no">
<div class="button-row">
		<button type="button" class="convert-button" data-toggle="modal" data-target="#myModal">Convert</button>
	<form>
		<input type="file" class="hidden"  id="uploadfiles" multiple="multiple" />
		<label class="upload-button"  for="uploadfiles">Upload files</label>
		<script src="main.js"></script>
	</form>
	<button type="button" class="convert-button" data-toggle="modal" data-target="#dataBaseModal">DB Store</button>
</div>

                <div class="modal fade" id="dataBaseModal" role="dialog">
    <div class="modal-dialog">
      <!-- Modal content-->
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal">&times;</button>
          <h4 class="modal-title">Choose a file to store in the database</h4>
        </div>
        <div class="modal-body">
                <p>
<?php
        foreach (glob("files/*.txt") as $filename){
                echo "<div class='select-files'>".basename($filename)."</div>";
	}
?>
</p>
                                </div>
                                <div class="modal-footer">
                                <input type="hidden" name="dataBase-store" value="" id="databaseStore"/>
                                <button type="button" class="btn btn-default" id="store" data-dismiss="modal">Submit</button>
                                </div>
                                </div>
                        </div>
                </div>








		<div class="modal fade" id="myModal" role="dialog">
    <div class="modal-dialog">
      <!-- Modal content-->
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal">&times;</button>
          <h4 class="modal-title">Choose a file to convert</h4>
        </div>
        <div class="modal-body">
          	<p>
<?php
        foreach (glob("files/*.txt") as $filename){
                echo "<div class='select-files'>".basename($filename)."</div>";
        }
?>
</p>
        			</div>
        			<div class="modal-footer">
				<input type="hidden" name="file-convert" value="" id="fileconvert"/>
          			<button type="button" class="btn btn-default" id="convert" data-dismiss="modal">Submit</button>
				</div>
      				</div>
    			</div>
  		</div>
</body>
</html>


<?php
	echo "<div class='my-files'>";
	$txtfiles = array();
	echo "<div class='txt-files'>";
	echo "<div class='txt-title'>.TXT Files<br></div>";
	foreach (glob("files/*.txt") as $filename){
		//echo "<a href=$filename>".basename($filename)."</a>";
		$txtfiles[] = "<a href=$filename>".basename($filename)."</a>";
	}
        sort($txtfiles);
        foreach ($txtfiles as $file){
                echo "<div>".$file."</div>";
        }
	echo "</div>";
	$htmlfiles = array();
        echo "<div class='html-files'>";
        echo "<div class='html-title'>HTML Files:<br></div>";
        foreach (glob("files/*.html") as $filename){
                //echo "<a href=$filename>".basename($filename)."</a>";
		$htmlfiles[] = "<a href=$filename>".basename($filename)."</a>";
        }
        foreach ($out as $item){
		//$whatIWant = substr($item, strpos($item, "/") + 1);   
		$htmlfiles[] = $item;  
                //echo "<div>".$item."</div>";
        }
	sort($htmlfiles);
	foreach ($htmlfiles as $file){
		echo "<div id='link'>".$file."</div>";
	}
        echo "</div>";

echo "</div>";
if (isset($_FILES['uploaded_file'])) {
    // Example:
    if(move_uploaded_file($_FILES['uploaded_file']['tmp_name'], "files/" . $_FILES['uploaded_file']['name'])){
        echo $_FILES['uploaded_file']['name']. " uploaded ...";
	header("Refresh:0");

    } else {
        echo $_FILES['uploaded_file']['name']. " NOT uploaded ...";
    }

    exit;
}

?>
