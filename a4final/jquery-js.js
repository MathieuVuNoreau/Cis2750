onload=function(){
var e=document.getElementById("refreshed");
if(e.value=="no")e.value="yes";
else{e.value="no";location.reload();}
}
$(document).ready(function(){
	$(".select-files").click(function () {
		$(".select-files").removeClass("active");
		$(this).addClass("active");
		$("input#fileconvert").attr('value', $(this).text());
	});
	$("#convert").on('click', function(){
		var file=$("#fileconvert").val();    
		$.ajax({
       			url: 'convert.php',
       			type:'POST',
			data: ({filename:file}),
       			success: function(data){
				console.log(data);
				location.reload();
				window.location="files/"+file+".html"
			}
    		});
	});
        $(".select-files").click(function () {
                $(".select-files").removeClass("active");
                $(this).addClass("active");
                $("input#databaseStore").attr('value', $(this).text());
        });

	$("#store").on('click', function(){
        	var file=$("#databaseStore").val();
		$.ajax({
       			url: 'store.php',
       			type:'POST',
        		data: ({filename:file}),
      			success: function(data){
                		console.log(data);
                                location.reload();
                                window.location = "dataBaseFile";
        		}
    		});
	});
	$('div#link').on('click', function(){
                var file=$(this).text();
                $.ajax({
                        url: 'newpage.php',
                        type:'POST',
                        data: ({filename:file}),
                        success: function(data){
                                console.log(data);
				window.location = "dataBaseFile";
                        }
                });
        });

});



