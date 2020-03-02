package main;

import java.util.Queue;
import java.util.concurrent.Executor;


public class SlaveThread extends Thread {
	boolean running = false;
	QueueMonitor q;
	

	public SlaveThread(QueueMonitor queue) {
		this.q = queue;
	}

	public void run() {
		while (true) {
			new Thread((Runnable)q.getNext()).start();
		}
	}

}
