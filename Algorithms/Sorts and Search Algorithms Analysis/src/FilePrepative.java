import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class FilePrepative {

    public static int[] excelToArray(String fileName, int no) throws IOException {
        int[] flowDuration =new int[no];
        int counter = 0;

        File file = new File(fileName);
        BufferedReader buffReader = new BufferedReader(new FileReader(file));
        String str;
        buffReader.readLine();

        while((str=buffReader.readLine()) != null){
            String[] arr = str.split(",");
            flowDuration[counter] = Integer.parseInt(arr[6]);
            counter++;
            if(counter == no){
                return flowDuration;
            }

        }
        return flowDuration;

    }
}
