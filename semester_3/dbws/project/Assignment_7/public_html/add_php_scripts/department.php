
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
            if(isset($_POST["submit"])){
                $name = $_POST["name"];
                $num_of_emps = $_POST["num_of_emps"];
                
                $sql = "INSERT INTO departments(num_of_emps, name) VALUES(
                    '$num_of_emps', '$name'
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
