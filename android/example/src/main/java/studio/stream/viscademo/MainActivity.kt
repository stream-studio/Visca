package studio.stream.viscademo

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import studio.stream.Visca



class StudioMainActivity : AppCompatActivity() {

    var visca: Visca? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        visca = Visca();
        visca?.panTilt(10, 10);
        setContentView(R.layout.activity_studio_main)
        

    }


}