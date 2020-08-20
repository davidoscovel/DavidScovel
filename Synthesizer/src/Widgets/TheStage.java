package Widgets;

import Synth.AudioClip;
import Synth.Speaker;
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.geometry.Point2D;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.*;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;
import javafx.stage.Stage;
import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import java.util.ArrayList;

public class TheStage extends Application {
    Widget input;
    Widget output;


    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        //Set the scene
        primaryStage.setTitle("Synthesizer");
        Button play = new Button("Play");
        Scene synth = new Scene(play);
        primaryStage.setScene(synth);
        Image background_image = new Image("LightArt.jpg");
        BackgroundSize bSize = new BackgroundSize(BackgroundSize.AUTO, BackgroundSize.AUTO, false, false, true, false);

        //Set position of Play button and initialize grid pane
        BorderPane stage = new BorderPane();

        stage.setBackground(new Background(new BackgroundImage(background_image,
                BackgroundRepeat.NO_REPEAT,
                BackgroundRepeat.NO_REPEAT,
                BackgroundPosition.CENTER,
                bSize)));

        Pane pane = new Pane();
        Pane cable_pane = new Pane();
        Pane line_pane = new Pane();
        ArrayList<Cable> cables = new ArrayList<>();

        //Create buttons that make new Wave Widgets
        //Sin Wave Button
        ArrayList<Widget> widgets = new ArrayList<>();
        Widget speaker = new SpeakerWidget("Speaker", cable_pane, cables);
        BorderPane speaker_display = speaker.display();
        speaker_display.relocate(850, 550);
        pane.getChildren().addAll(speaker_display);
        widgets.add(speaker);
        MenuItem create_sinwave = new MenuItem("Sin Wave");
        create_sinwave.setOnAction(e -> {
            Widget sin_wave = new SinWaveWidget("Sin Wave", cable_pane, cables);
            BorderPane  display = sin_wave.display();
            pane.getChildren().add(display);
            widgets.add(sin_wave);
        });
        //Square Wave Button
        MenuItem create_square_wave = new MenuItem("Square Wave");
        create_square_wave.setOnAction(e ->{
            Widget square_wave = new SquareWaveWidget("Square Wave", cable_pane, cables);
            BorderPane display = square_wave.display();
            pane.getChildren().add(display);
            widgets.add(square_wave);
        });
        //Descending Wave Button
        MenuItem create_descending_wave = new MenuItem("Descending Wave");
        create_descending_wave.setOnAction(e ->{
            Widget descending_wave = new DescendingWaveWidget("Descending Wave", cable_pane, cables);
            BorderPane display = descending_wave.display();
            pane.getChildren().add(display);
            widgets.add(descending_wave);
        });
        //Ascending Wave Button
        MenuItem create_ascending_wave = new MenuItem("Ascending Wave");
        create_ascending_wave.setOnAction(e ->{
            Widget ascending_wave = new AscendingWaveWidget("Ascending Wave", cable_pane, cables);
            BorderPane display = ascending_wave.display();
            pane.getChildren().add(display);
            widgets.add(ascending_wave);
        });

        //Volume Button
        MenuItem volume_widget = new MenuItem("Volume");
        volume_widget.setOnAction(e ->{
            Widget volume_wig = new VolumeWidget("Volume", cable_pane, cables);
            BorderPane display = volume_wig.display();
            pane.getChildren().add(display);
            widgets.add(volume_wig);
        });


        //Mixer Button
        MenuItem mixer_widget = new MenuItem("Mixer");
        mixer_widget.setOnAction(e ->{
            Widget mixer_wig = new MixerWidget("Mixer", cable_pane, cables);
            BorderPane display = mixer_wig.display();
            pane.getChildren().add(display);
            widgets.add(mixer_wig);
        });

        //Add Clear all button
        MenuItem clear = new MenuItem("Clear all");
        clear.setStyle("-fx-border-width: 2;" +
        "-fx-border-color: Red;");
        clear.setOnAction(e ->{
            widgets.clear();
            cables.clear();
            pane.getChildren().clear();
            cable_pane.getChildren().clear();
            speaker.setAudioComponent(new Speaker());
            BorderPane speaker_display1 = speaker.display();
            speaker_display.relocate(850, 550);
            pane.getChildren().addAll(speaker_display, line_pane, cable_pane);
            widgets.add(speaker);

        });

        //Add Widgets Menu
        MenuButton menu = new MenuButton("Add...",null, create_sinwave, create_square_wave, create_descending_wave, create_ascending_wave, volume_widget, mixer_widget, clear);





        //React to play button
        play.setOnAction(e -> {
            //get properties from the system about samples rates, etc
            try {
                Clip c = AudioSystem.getClip(); //terrible name
                //This is the format that we're following, 44.1KHz mono audio, 16 bits per sample
                AudioFormat format16 = new AudioFormat(44100, 16, 1, true, false);
                AudioClip clip = speaker.getAudioComponent().getClip();
                c.open(format16, clip.getData(), 0, clip.getData().length); //reads data from my byte array to play it
                c.start(); //plays it


            } catch (LineUnavailableException ex) {
                ex.printStackTrace();
            }
        });

        //Dynamic Line Drawing and Cabling
        Line dynamic = new Line();

        final boolean[] pressed = {false};
        dynamic.setStyle("-fx-stroke: White;" +
                "-fx-border-color: Black;" +
                "-fx-stroke-width: 3;");
        pane.addEventHandler(MouseEvent.MOUSE_PRESSED,
                new EventHandler<MouseEvent>() {
                    @Override

                    public void handle(MouseEvent mouseEvent) {
                        for(Widget w: widgets) {
                            if(w.get_output_jack() == null){continue;}
                            if((w.get_output_jack().isPressed())) {
                                pressed[0] = true;
                                output = w;
                                dynamic.setStartX(mouseEvent.getX());
                                dynamic.setStartY(mouseEvent.getY());

                                pane.addEventHandler(MouseEvent.MOUSE_DRAGGED,
                                        new EventHandler<MouseEvent>() {
                                            @Override
                                            public void handle(MouseEvent mouseEvent) {
                                                if(pressed[0]){
                                                dynamic.setEndX(mouseEvent.getX());
                                                dynamic.setEndY(mouseEvent.getY());
                                                if(!line_pane.getChildren().contains(dynamic)) {
                                                    line_pane.getChildren().add(dynamic);
                                                }
                                            }
                                            }
                                        });

                                pane.addEventHandler(MouseEvent.MOUSE_RELEASED,
                                        new EventHandler<MouseEvent>() {
                                            @Override
                                            public void handle(MouseEvent mouseEvent) {
                                                pressed[0] = false;
                                                for(Widget i: widgets){
                                                    input = i;
                                                    if(input.get_input_jack() == null){continue;};
                                                    Circle ij = input.get_input_jack();
                                                    dynamic.setEndX(mouseEvent.getX());
                                                    dynamic.setEndY(mouseEvent.getY());
                                                    Point2D release_point = new Point2D(mouseEvent.getX(), mouseEvent.getY());
                                                    if((ij.localToScene(ij.getBoundsInLocal())).contains(release_point)){
                                                        if(input.get_input_jack() != output.get_input_jack()) {
                                                            Cable cable = new Cable(output, input, cable_pane);
                                                            cables.add(cable);
                                                        }
                                                    }
                                                }
                                                line_pane.getChildren().clear();
                                            }
                                        });
                            }

                        }

                    }

                });



        stage.setBottom(play);
        stage.setRight(menu);
        stage.setAlignment(play, Pos.CENTER_RIGHT);
        line_pane.toFront();
        cable_pane.toFront();
        pane.getChildren().addAll(line_pane, cable_pane);
        stage.setCenter(pane);
        line_pane.toFront();
        primaryStage.setScene(new Scene(stage, 1000, 672));
        primaryStage.show();
    }
}
