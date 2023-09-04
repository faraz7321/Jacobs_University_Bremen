<html>
    <head>SIUU</head>
    <body>
        <?php
            header("Location: ../add_forms/redirect.html");
            // create connection
            $conn = mysqli_connect("localhost", "group30", "apachewhich", "group30");
            if (mysqli_connect_errno()) {
                echo "Failed to connect to DB!";
                exit();
            }
            // echo "yeet";
            if(isset($_POST["submit"])){
                $name = $_POST["name"];
                $num_of_items = $_POST["num_of_items"];
                
                $sql = "INSERT INTO categories(c_name, num_of_items) VALUES(
                    '$name', '$num_of_items'
                    )";
                if(mysqli_query($conn, $sql)){
                    echo "Record Added Successfully.";
                }else{
                    echo "Error inserting: " . mysqli_error($conn) . "<br>";
                }
            }
            $conn->close();
        ?>
    </body>
</html>
