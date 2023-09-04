
<html>
    <head>SIUU</head>
    <body>
        <?php
            header("Location: ../forms/redirect.html");
            // create connection
            $conn = mysqli_connect("localhost", "group30", "apachewhich", "group30");
            if (mysqli_connect_errno()) {
                echo "Failed to connect to DB!";
                exit();
            }
            if(isset($_POST["submit"])){
                $item_name = $_POST["item_name"];
                $category = $_POST["category"];
                $quantity = $_POST["quantity"];
                $is_consumable = $_POST["consumable"]; 
                if(strcmp($is_consumable, "Yes") == 0){               
                $sql = "INSERT INTO items(item_name, isConsumable, quantity, category) VALUES(
                    '$item_name', 1, '$quantity', '$category'
                    )";
                }else{
                    $sql = "INSERT INTO items(item_name, isConsumable, quantity, category) VALUES(
                        '$item_name', 0, '$quantity', '$category'
                        )";
                }
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
