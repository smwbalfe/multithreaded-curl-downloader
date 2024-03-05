- **Title:** Multithreaded Curl Downloader

- **Description:** A high-performance, multithreaded downloader built using C++ and libcurl. This tool is designed to efficiently download files from the internet by leveraging the power of multithreading and the robustness of libcurl.

- **Features:**
  - **Multithreading Support:** Utilizes a thread pool to handle multiple download tasks concurrently, significantly reducing the total download time for multiple files.
  - **libcurl Integration:** Employs libcurl for stable and flexible HTTP/HTTPS file downloads, supporting a wide range of protocols.
  - **Progress Tracking:** Includes functionality to monitor and display the progress of each download task, providing real-time feedback to the user.
  - **Header Management:** Offers capabilities to handle HTTP headers effectively, allowing for custom requests and responses.
  - **Customizable Download Options:** Users can customize various download parameters, such as setting headers, to meet specific requirements.

- **Technologies Used:**
  - **C++:** The core programming language used for developing the downloader, ensuring high performance and system-level control.
  - **libcurl:** A client-side URL transfer library, supporting a variety of protocols and features for downloading files over the internet.
  - **CMake:** Utilized for building, testing, and packaging the software, making it easy to compile and run on different platforms.
  - **Thread Pool Implementation:** A custom thread pool implementation is used to manage multiple threads efficiently, optimizing resource usage and improving download speeds.
