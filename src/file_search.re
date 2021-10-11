open Lwt;
open Cohttp_lwt_unix;
open Anime;

let search_image_file = file_path => {
  let file_content = File.get_file(file_path);

  let endpoint = "https://api.trace.moe/search?anilistInfo";
  let fetch = {
    let url = Uri.of_string(endpoint);
    let boundary = "----" ++ Util.gen_boundary(24);
    let content_type = "multipart/form-data; boundary=" ++ boundary;
    let headers = Cohttp.Header.of_list([("Content-Type", content_type)]);

    let value =
      "--"
      ++ boundary
      ++ "\r\n"
      ++ "Content-Disposition: form-data; name=\""
      ++ "image"
      ++ "\"";

    let form_value = value ++ "; filename=\"" ++ file_path ++ "\"\r\n";

    let post_data =
      form_value
      ++ "Content-Type: {content-type header}\r\n\r\n"
      ++ file_content
      ++ "\r\n";

    let data = post_data ++ "--" ++ boundary ++ "--";

    let body = Cohttp_lwt.Body.of_string(data);
    print_endline("Loading... \n");

    Client.post(url, ~headers, ~body)
    >>= (
      ((_, body)) =>
        Cohttp_lwt.Body.to_string(body)
        >>= (
          body => {
            let anime =
              switch (anime_of_yojson(Yojson.Safe.from_string(body))) {
              | Ok(anime) => anime
              | Error(_) => failwith("Invalid file")
              };
            return(anime_response(anime));
          }
        )
    );
  };
  Lwt_main.run(fetch) |> ignore;
};
