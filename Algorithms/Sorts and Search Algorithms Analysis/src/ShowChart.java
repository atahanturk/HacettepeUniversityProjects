import org.knowm.xchart.*;
import org.knowm.xchart.style.Styler;
import javax.imageio.IIOException;
import java.io.IOException;
import org.knowm.xchart.BitmapEncoder.BitmapFormat;

public class ShowChart {

    public static void showChart(String title, double[][]yAxis, String yAxisName, String algoType) throws IOException {
        XYChart chart = new XYChartBuilder().height(800).width(800).title(title).yAxisTitle(yAxisName).xAxisTitle("Input Size").build();
        double[] xAxis = new double[] {500,1000,2000,4000,8000,16000,32000,64000,128000,250000};

        if(algoType == "sorting"){
            chart.addSeries("Selection Sort", xAxis, yAxis[0]);
            chart.addSeries("Quick Sort", xAxis, yAxis[1]);
            chart.addSeries("Bucket Sort", xAxis, yAxis[2]);

        }else if(algoType == "searching"){
            chart.addSeries("Linear Search on Random Data", xAxis,yAxis[0]);
            chart.addSeries("Linear Search on Sorted Data", xAxis, yAxis[1]);
            chart.addSeries("Binary Search on Sorted Data", xAxis, yAxis[2]);
        }
        chart.getStyler().setLegendPosition(Styler.LegendPosition.InsideNE);
        chart.getStyler().setDefaultSeriesRenderStyle(XYSeries.XYSeriesRenderStyle.Line);
        BitmapEncoder.saveBitmap(chart, title + ".png", BitmapEncoder.BitmapFormat.PNG);
        new SwingWrapper(chart).displayChart();

    }
}
