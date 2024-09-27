<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    
    <!-- Root template -->
    <xsl:template match="/">
        <html>
            <head>
                <title>Student Details</title>
                <style>
                    table {
                        width: 50%;
                        border-collapse: collapse;
                        margin: 20px 0;
                    }
                    th, td {
                        border: 1px solid #ddd;
                        padding: 8px;
                        text-align: left;
                    }
                    th {
                        background-color: #f2f2f2;
                    }
                </style>
            </head>
            <body>
                <h2>Student Details</h2>
                <table>
                    <tr>
                        <th>Name</th>
                        <th>Roll No</th>
                        <th>Department</th>
                        <th>Year</th>
                        <th>University</th>
                    </tr>
                    <xsl:for-each select="students/student">
                        <tr>
                            <td><xsl:value-of select="name"/></td>
                            <td><xsl:value-of select="rollno"/></td>
                            <td><xsl:value-of select="department"/></td>
                            <td><xsl:value-of select="year"/></td>
                            <td><xsl:value-of select="university"/></td>
                        </tr>
                    </xsl:for-each>
                </table>
            </body>
        </html>
    </xsl:template>

</xsl:stylesheet>
