(function () {

    var uploadfiles = document.querySelector('#uploadfiles');
    uploadfiles.addEventListener('change', function () {
        var files = this.files;
        for(var i=0; i<files.length; i++){
            uploadFile(this.files[i]);
        }

    }, false);


    function uploadFile(file){
console.log("send help");
        var url = "a4.php";
        var xhr = new XMLHttpRequest();
        var fd = new FormData();
        xhr.open("POST", url, true);
        xhr.onreadystatechange = function() {
            if (xhr.readyState == 4 && xhr.status == 200) {
                // Every thing ok, file uploaded
                location.reload();
                console.log(xhr.responseText); // handle response
            }
        };
        fd.append('uploaded_file', file);
        xhr.send(fd);
    }
}());

