<?php include "./connection.php"; ?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta name="viewport" content="width=device-width" , initial-scale="1.0">
    <title>PMS</title>
    <link rel="icon" href="../images/favicon.png">
    <link rel="stylesheet" href="../css/style.css">
</head>

<body>
    <div class="topbar">
        <a href="about.html">About</a>
        <a href="imprint.html">Imprint</a>
    </div>
    <div class="sidebar">
        <a href="index.html">
            <img src="../images/favicon.png" alt="logo">
        </a>
        <a href="../index.html">Home</a>
        <a href="../inventory.html">Inventory</a>
        <a href="../maintenance.html">Maintenance</a>
        <a href="../search.html" id="current">Search</a>
        <!-- <a href="contact.html">Contact</a> -->
    </div>
    <div class="page">
        <div class="form">
            <form action="employees.php" method="post">
                <label for="department">List all employees in</label>
                <select name="dname" id="department" required>
                    <option value="none" selected disabled>Choose a Department</option>
                    <?php
                    $sql = mysqli_query($conn, "SELECT name FROM departments;");
                    while ($row = $sql->fetch_assoc()) {
                    ?>
                        <option><?php echo $row["name"]; ?></option>
                    <?php
                    }
                    ?>
                </select>
                <!-- <input type="name" name="d_name" placeholder="Name"> -->
                <input type="submit" value="Search" name="submit" style="margin-left: 293px; text-align:center;">
            </form>
        </div>
        <div class="results">
            <?php
            if (isset($_POST["submit"])) {
                $d_name = $_POST["dname"];
                $sql = "SELECT d_id FROM departments WHERE name='$d_name'";
                $result = mysqli_query($conn, $sql);
                $row = $result->fetch_assoc();
                $d_id = $row["d_id"];
                $sql = "SELECT * FROM admins WHERE d_id=$d_id";
                // echo "ssiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu".$result->fetch_row()[0];
                $admins = mysqli_query($conn, $sql);
                echo "<h1 style='text-decoration: underline; margin-left:200px;'>Admins:</h1>";
                echo "<ul style='margin-left: 200px;'>";
                while ($row = $admins->fetch_assoc()) {
            ?>
                    <?php $id = $row["id"]; ?>
                    <li>
                        <a href="./details.php?id=<?php echo $row['id']; ?>&table=admins"><?php
                            $sql = "SELECT full_name FROM person WHERE id=$id";
                            $result = mysqli_query($conn, $sql);
                            echo $result->fetch_row()[0];
                            ?>
                        </a>
                    </li>
                <?php
                }
                ?>
                </ul>
                <?php
                $sql = "SELECT * FROM employees WHERE d_id=$d_id";
                // echo "ssiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu".$result->fetch_row()[0];
                $emps = mysqli_query($conn, $sql);
                echo "<h1 style='text-decoration: underline; margin-left:200px;'>Employees:</h1>";
                echo "<ul style='margin-left: 200px;'>";
                while ($row = $emps->fetch_assoc()) {
                ?>
                    <li>
                        <a href="./details.php?id=<?php echo $row['id']; ?>&table=employees"><?php
                                                                                                $id = $row["id"];
                                                                                                $sql = "SELECT full_name FROM person WHERE id=$id";
                                                                                                $name = mysqli_query($conn, $sql);
                                                                                                echo $name->fetch_row()[0];
                                                                                                ?>
                        </a>
                    </li>
            <?php
                }
            }
            ?>
            </ul>

        </div>






        <p id="imprint">
            This website is student lab work and does not necessarily reflect Jacobs University Bremen opinions. Jacobs
            University Bremen does not endorse this site, nor is it checked by Jacobs University
            Bremen regularly, nor is it part of the official Jacobs University Bremen web presence.
            For each external link existing on this website, we initially have checked that the target page
            does not contain contents which is illegal wrt. German jurisdiction. However, as we have no influence on
            such contents, this may change without our notice. Therefore we deny any responsibility for the websites
            referenced through our external links from here.
            No information conflicting with GDPR is stored in the server.
        </p>
    </div>
</body>

</html>