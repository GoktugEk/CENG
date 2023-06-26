package ceng.ceng351.cengvacdb;


import java.sql.*;
import java.util.ArrayList;

public class CENGVACDB implements ICENGVACDB{

    private Statement statement;
    private Connection connection;

    @Override
    public void initialize() {
        try {
            this.connection = DriverManager.getConnection("jdbc:mysql://144.122.71.121:8080/db2380343?useSSL=false", "e2380343", "ypk$hC4ujU?T");
            this.statement = connection.createStatement();
        }
        catch (Exception exception){
            exception.printStackTrace();
        }
    }



    @Override
    public int createTables() {
        int count = 0;
        try{
            PreparedStatement stat = connection.prepareStatement("CREATE TABLE IF NOT EXISTS User( " +
                    "                    userID INTEGER PRIMARY KEY, " +
                    "                    userName varchar(45), " +
                    "                    age integer, " +
                    "                    address varchar(150) , " +
                    "                    password varchar(30), " +
                    "                    status varchar(15));");
            stat.executeUpdate();
            count++;
        }catch(SQLException e){
            e.printStackTrace();
        }
        try{
            PreparedStatement stat = connection.prepareStatement("CREATE TABLE IF NOT EXISTS Vaccine( " +
                    "  code integer PRIMARY key, " +
                    "  vaccinename varchar(30), " +
                    "  type varchar(30) );");
            stat.executeUpdate();
            count++;
        }catch(SQLException e){
            e.printStackTrace();
        }
        try{
            PreparedStatement stat = connection.prepareStatement("CREATE TABLE IF NOT EXISTS Vaccination ( " +
                    "  code integer not NULL,  " +
                    "  userID integer not NULL, " +
                    "  dose integer, " +
                    "  vacdate date, " +
                    "  PRIMARY KEY (userID,code,dose), " +
                    "  FOREIGN key (userID) REFERENCES User(userID), " +
                    "  FOREIGN KEY (code) REFERENCES Vaccine(code) on delete CASCADE);");

            stat.executeUpdate();
            count++;
        }catch(SQLException e){
            e.printStackTrace();
        }

        try{
            PreparedStatement stat = connection.prepareStatement("CREATE TABLE  AllergicSideEffect ( " +
                    "  effectcode integer PRIMARY KEY, " +
                    "  effectname varchar(50));");

            stat.executeUpdate();
            count++;
        }catch(SQLException e){
            e.printStackTrace();
        }

        try {
            PreparedStatement stat = connection.prepareStatement("CREATE TABLE IF NOT EXISTS Seen( " +
                    "  effectcode integer, " +
                    "  code integer, " +
                    "  userID integer, " +
                    "  date date, " +
                    "  degree varchar(30), " +
                    "  primary key ( effectcode, code, userID)," +
                    "  foreign key (effectcode) references AllergicSideEffect(effectcode) on delete CASCADE, " +
                    "  foreign key (code) references Vaccine(code) ON DELETE CASCADE, " +
                    "  foreign key (userID) references User(userID)" +
                    "); ");
            stat.executeUpdate();
            count++;
        }catch (SQLException e){
            e.printStackTrace();
        }
        return count;
    }
    @Override
    public int dropTables() {
        int count = 0;
        try{
            PreparedStatement stat = connection.prepareStatement("DROP TABLE IF EXISTS Seen;");
            stat.executeUpdate();
            count++;
        }catch(Exception e){
            e.printStackTrace();
        }
        try{
            PreparedStatement stat = connection.prepareStatement("DROP TABLE IF EXISTS AllergicSideEffect;");
            stat.executeUpdate();
            count++;
        }catch(Exception e){
            e.printStackTrace();
        }

        try{
            PreparedStatement stat = connection.prepareStatement("DROP TABLE IF EXISTS Vaccination;");
            stat.executeUpdate();
            count++;
        }catch(Exception e){
            e.printStackTrace();
        }
        try{
            PreparedStatement stat = connection.prepareStatement("DROP TABLE IF EXISTS Vaccine;");
            stat.executeUpdate();
            count++;
        }catch(Exception e){
            e.printStackTrace();
        }

        try{
            PreparedStatement stat = connection.prepareStatement("DROP TABLE IF EXISTS User;");
            stat.executeUpdate();
            count++;
        }catch(Exception e){
            e.printStackTrace();
        }

        return count;
    }

    @Override
    public int insertUser(User[] users) {
        int count = 0;
        for (int i = 0; i < users.length; i++) {
            try{
                String query = "INSERT INTO User VALUES (" + users[i].getUserID() + ",'" +
                        users[i].getUserName() + "'," +
                        users[i].getAge() + ",'" +
                        users[i].getAddress() + "','" +
                        users[i].getPassword() + "','" +
                        users[i].getStatus() + "');";
                PreparedStatement stat = connection.prepareStatement(query);
                stat.executeUpdate();
                count++;
            }catch(Exception e){
                e.printStackTrace();
            }
        }
        return count;
    }

    @Override
    public int insertAllergicSideEffect(AllergicSideEffect[] sideEffects) {
        int count = 0;
        for (int i = 0; i < sideEffects.length; i++) {
            try {
                AllergicSideEffect iter = sideEffects[i];
                String efcode = String.valueOf(iter.getEffectCode()) + ",\"";
                String efname = iter.getEffectName() + '"';
                String res = "INSERT INTO AllergicSideEffect VALUES (" + efcode + efname + ')';

                PreparedStatement stat = connection.prepareStatement(res);
                stat.executeUpdate();
                count++;
            }catch (Exception e){
                e.printStackTrace();
            }

        }
        return count;
    }

    @Override
    public int insertVaccine(Vaccine[] vaccines) {
        int count = 0;
        for (int i = 0; i < vaccines.length; i++) {
            try {
                String code = String.valueOf(vaccines[i].getCode())+ ',';
                String vacname = "'" + vaccines[i].getVaccineName()+ "',";
                String type = "'" + vaccines[i].getType() + "'";
                PreparedStatement stat = connection.prepareStatement("INSERT INTO Vaccine VALUES (" + code + vacname + type + ")");
                stat.executeUpdate();
                count++;
            }catch (Exception e){
                e.printStackTrace();
            }
        }
        return count;
    }

    @Override
    public int insertVaccination(Vaccination[] vaccinations) {
        int count = 0;
        for (int i = 0; i <vaccinations.length; i++) {
            try {
                Vaccination iter = vaccinations[i];
                String res = String.valueOf(iter.getCode()) + ',' + iter.getUserID() + ','+ iter.getDose() + ",'" + iter.getVacdate() +"'";
                PreparedStatement stat = connection.prepareStatement("INSERT INTO Vaccination VALUES (" + res + ");");
                stat.executeUpdate();
                count++;
            }catch (Exception e){
                e.printStackTrace();
            }

        }

        return count;
    }

    @Override
    public int insertSeen(Seen[] seens) {
        int count = 0;
        for (int i = 0; i <seens.length; i++) {
            try {
                Seen iter = seens[i];

                String  res = String.valueOf(iter.getEffectcode()) + ',' + iter.getCode() + ",\"" + iter.getUserID() + "\",\"" +
                        iter.getDate() + "\",\"" + iter.getDegree() + "\"";

                PreparedStatement stat = connection.prepareStatement("INSERT INTO Seen VALUES (" + res + ")");
                stat.executeUpdate();
                count++;
            }catch (Exception e){
                e.printStackTrace();
            }

        }
        return count;
    }







    @Override
    public Vaccine[] getVaccinesNotAppliedAnyUser() {
        ArrayList<Vaccine> resarr = new ArrayList<>();
        String query=
                "Select V.code,V.vaccinename,V.type \n" +
                        "                        from Vaccine V \n" +
                        "                         \n" +
                        "                        where V.code NOT IN\n" +
                        "                         \n" +
                        "                        (Select V.code\n" +
                        "                        from Vaccine V, Vaccination T \n" +
                        "                        where V.code = T.code \n" +
                        "                        order by V.code); ";
        ;
        try {
            PreparedStatement stat = connection.prepareStatement(query);
            ResultSet rsltst =  stat.executeQuery();

            while (rsltst.next()) {
                resarr.add(new Vaccine(
                        rsltst.getInt("code"),
                        rsltst.getString("vaccinename"),
                        rsltst.getString("type")
                ));
            }


        } catch (SQLException e) {
            e.printStackTrace();
        }
        return resarr.toArray(new Vaccine[0]);
    }


    @Override
    public QueryResult.UserIDuserNameAddressResult[] getVaccinatedUsersforTwoDosesByDate(String vacdate) {
        String query = "SELECT U.userid,U.username,U.address \n" +
                "FROM User U  \n" +
                "WHERE Not exists (SELECT *\n" +
                "                 from Vaccination V\n" +
                "                 where V.userID = U.userID AND V.vacdate > \""+ vacdate+"\" and\n" +
                "                 V.dose = 3)\n" +
                "                 and EXISTS (SELECT *  \n" +
                "             FROM Vaccination V \n" +
                "             WHERE V.userID = U.userID and  \n" +
                "              V.vacdate > \""+vacdate+"\" and  \n" +
                "              V.dose = 2 AND EXISTS (select * from Vaccination V2 \n" +
                "                                    where V2.userID = U.userID and  \n" +
                "                                     V2.vacdate > \""+vacdate+"\" and \n" +
                "                                     V2.dose = 1)) \n" +
                "ORDER by U.userID;";
        ArrayList<QueryResult.UserIDuserNameAddressResult> resarr = new ArrayList<>();
        try {
            PreparedStatement stat = connection.prepareStatement(query);
            ResultSet res = stat.executeQuery();

            while(res.next()){
                resarr.add(new QueryResult.UserIDuserNameAddressResult(res.getInt("userID"),
                        res.getString("userName"),
                        res.getString("address")));
            }

            return resarr.toArray(new QueryResult.UserIDuserNameAddressResult[0]);

        }catch (SQLException e){
            e.printStackTrace();
        }
        return resarr.toArray(new QueryResult.UserIDuserNameAddressResult[0]);
    }

    @Override
    public Vaccine[] getTwoRecentVaccinesDoNotContainVac() {
        String query = "SelecT DISTINCT V.code,V.vaccinename,V.type,T.vacdate \n" +
                "from Vaccine V, Vaccination T \n" +
                "where V.code = T.code and V.code NOT IN (\n" +
                "                                select V2.code \n" +
                "                                from Vaccine V2,Vaccination T2\n" +
                "                                where V2.vaccinename  LIKE \"%vac%\" and V2.code = T2.code )\n" +
                "order by T.vacdate DESC,V.code DESC";
        ArrayList<Vaccine> resarr = new ArrayList<>();
        try {
            PreparedStatement stat = connection.prepareStatement(query);
            ResultSet res = stat.executeQuery();
            int i = 0;
            int duplicate = 0;
            res.next();
            do{
                if(res.getInt("code") == duplicate){
                    continue;
                }
                else {
                    duplicate = res.getInt("code");
                    resarr.add(new Vaccine(res.getInt("code"),
                            res.getString("vaccinename"),
                            res.getString("type")));
                    i++;
                }

            }while(i < 2 && res.next());

            return resarr.toArray(new Vaccine[0]);
        }catch(SQLException e){e.printStackTrace();}

        return resarr.toArray(new Vaccine[0]);
    }

    @Override
    public QueryResult.UserIDuserNameAddressResult[] getUsersAtHasLeastTwoDoseAtMostOneSideEffect() {

        String query = "SELECT U.userID,U.username,U.address \n" +
                "                FROM User U \n" +
                "                WHERE EXISTS (SELECT * \n" +
                "                             FROM Vaccination V \n" +
                "                             WHERE V.userID = U.userID and \n" +
                "                              V.dose = 1 AND EXISTS (select * from Vaccination V2 \n" +
                "                                                    where V2.userID = U.userID and \n" +
                "                                                     V2.dose = 2)) AND not exists(\n" +
                "                                                       select * from Seen S,Seen S2             \n" +
                "                                                       where S.userID = U.userID and S.userID = S2.userID and \n" +
                "                                                       (S.effectcode != S2.effectcode or\n" +
                "                                                        S.code != S2.code or S.date != S2.date or \n" +
                "                                                        S.degree != S2.degree)) \n" +
                "ORDER by U.userID;";


        ArrayList<QueryResult.UserIDuserNameAddressResult> resarr = new ArrayList<>();
        try {
            statement = connection.createStatement();
            ResultSet res = statement.executeQuery(query);

            while (res.next()){
                resarr.add(new QueryResult.UserIDuserNameAddressResult(
                        res.getInt("userID"),
                        res.getString("userName"),
                        res.getString("address")));
            }



        }catch(SQLException e){
            e.printStackTrace();
        }
        return resarr.toArray(new QueryResult.UserIDuserNameAddressResult[0]);
    }

    @Override
    public QueryResult.UserIDuserNameAddressResult[] getVaccinatedUsersWithAllVaccinesCanCauseGivenSideEffect(String effectname) {
        ArrayList<QueryResult.UserIDuserNameAddressResult> resarr = new ArrayList<>();
        String query= "select DIstinct U.userID, U.username, U.address \n" +
                "from User U \n" +
                "where EXISTS (select V.code \n" +
                "from Vaccine V,Seen S,AllergicSideEffect A \n" +
                "where V.code = S.code and A.effectcode = S.effectcode and A.effectname = \"" + effectname + "\") AND not exists (select V.code \n" +
                "from Vaccine V,Seen S,AllergicSideEffect A \n" +
                "where V.code = S.code and A.effectcode = S.effectcode and A.effectname = \"" + effectname + "\" AND \n" +
                "                  V.code NOT IN \n" +
                "                    (select V.code \n" +
                "                    from Vaccination V \n" +
                "                    where V.userID = U.userID)) \n" +
                "order by U.userID;";

        try {
            PreparedStatement stat = connection.prepareStatement(query);
            ResultSet res = stat.executeQuery();

            while (res.next()){
                resarr.add(new QueryResult.UserIDuserNameAddressResult(res.getInt("userID"),
                        res.getString("userName"),
                        res.getString("address")));
            }

            return resarr.toArray(new QueryResult.UserIDuserNameAddressResult[0]);

        }catch(SQLException e){
            e.printStackTrace();
        }
        return new QueryResult.UserIDuserNameAddressResult[0];
    }

    @Override
    public QueryResult.UserIDuserNameAddressResult[] getUsersWithAtLeastTwoDifferentVaccineTypeByGivenInterval(String startdate, String enddate) {
        ArrayList<QueryResult.UserIDuserNameAddressResult> resarr = new ArrayList<>();
        String query = "SELECT U.userID, U.username, U.address \n" +
                "from User U \n " +
                "where exists (select *  \n" +
                "             from Vaccination V, Vaccination V2 \n" +
                "             where V.userID = U.userID and V.userID = V2.userID and \n" +
                "              V.vacdate >= \" " + startdate + "\" and V.vacdate <= \""+ enddate +"\" AND\n " +
                "              V2.vacdate >= \" " + startdate + "\" and V2.vacdate <= \""+ enddate +"\" AND \n" +
                "             V.code != V2.code and V.dose != V2.dose)\n " +
                "order by U.userID;";
        try {
            PreparedStatement stat = connection.prepareStatement(query);
            ResultSet res = stat.executeQuery();

            while (res.next()){

                resarr.add(new QueryResult.UserIDuserNameAddressResult(res.getInt("userID"),
                        res.getString("userName"),
                        res.getString("address")));
            }
        }catch(SQLException e){
            e.printStackTrace();
        }
        return resarr.toArray(new QueryResult.UserIDuserNameAddressResult[0]);
    }

    @Override
    public AllergicSideEffect[] getSideEffectsOfUserWhoHaveTwoDosesInLessThanTwentyDays() {
        ArrayList<AllergicSideEffect> resarr = new ArrayList<AllergicSideEffect>();
        String query = "select DISTINCT A.effectcode, A.effectname \n" +
                "from AllergicSideEffect A, Seen S, User U \n" +
                "WHERE A.effectcode = S.effectcode and S.userID = U.userID and\n" +
                "Exists(select V.userID\n" +
                "      from Vaccination V, Vaccination V2 \n" +
                "      where V2.userID = V.userID and V.userID = U.userID and\n" +
                "       V.vacdate > V2.vacdate and\n" +
                "       DATEDIFF(V.vacdate, V2.vacdate) < 20 AND \n" +
                "      V.dose != V2.dose) \n" +
                "order by A.effectcode;";
        try {
            PreparedStatement stat = connection.prepareStatement(query);
            ResultSet res = stat.executeQuery();

            while (res.next()){
                resarr.add(new AllergicSideEffect(res.getInt("effectcode"),
                        res.getString("effectname")));
            }
            return resarr.toArray(new AllergicSideEffect[0]);
        }catch(SQLException e){
            e.printStackTrace();
        }
        return new AllergicSideEffect[0];
    }

    @Override
    public double averageNumberofDosesofVaccinatedUserOverSixtyFiveYearsOld() {
        String query = "select AVG(DOSE)" +
                "from (select MAX(V.dose) as DOSE" +
                "     from Vaccination V, User U" +
                "     where U.userID = V.userID and U.age >65" +
                "     group by U.userid) T;";
        try {
            PreparedStatement stat = connection.prepareStatement(query);
            ResultSet res = stat.executeQuery();

            if (res.next()){
                return res.getDouble(1);
            }
        }catch(SQLException e){
            e.printStackTrace();
        }
        return 0;
    }

    @Override
    public int updateStatusToEligible(String givendate) {
        int count = 0;
        String query = "SELECT U.userID\n" +
                "from User U\n" +
                "where exists (select V.userID \n" +
                "              from Vaccination V,(select MAX(V2.dose) as LAST,V2.userID\n" +
                "                      from Vaccination V2\n" +
                "                      where V2.userID = U.userID \n" +
                "                      group by V2.userID) M\n" +
                "              where V.userID = U.userID and M.userID = V.userID \n" +
                "              AND  V.dose = M.LAST and DATEDIFF(\"" + givendate +"\",V.vacdate) >= 120)\n";
        try {
            PreparedStatement stat = connection.prepareStatement(query);
            ResultSet res = stat.executeQuery();

            String upquery = "UPDATE User " +
                    "set status = \"eligible\"" +
                    "where status = \"Not_Eligible\" and userID = ";

            while (res.next()){
                try {

                    stat = connection.prepareStatement(upquery + res.getInt(1) + ';');
                    count += stat.executeUpdate();
                }catch (SQLException e1){e1.printStackTrace();}
            }


            return count;
        }catch(SQLException e){
            e.printStackTrace();
        }
        return count;
    }

    @Override
    public Vaccine deleteVaccine(String vaccineName) {
        try {
            PreparedStatement stat = connection.prepareStatement("SELECT * FROM Vaccine where vaccinename = '" + vaccineName +"'");
            ResultSet res = stat.executeQuery();
            stat = connection.prepareStatement("DELETE FROM Vaccine WHERE vaccinename = '" + vaccineName + "'");
            stat.executeUpdate();

            while(res.next()){
                Vaccine ret = new Vaccine(res.getInt(1), res.getString(2), res.getString(3));
                return ret;
            }
        }catch(Exception e){
            e.printStackTrace();
        }


        return null;
    }



}

