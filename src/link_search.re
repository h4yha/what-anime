open Lwt;
open Cohttp_lwt_unix;
open Anime;

let search_image_link = url => {
  let endpoint = "https://api.trace.moe/search?anilistInfo&url=" ++ url;

  let fetch = {
    let url = Uri.of_string(endpoint);
    print_endline("Loading... \n");
    Client.get(url)
    >>= (
      ((_, body)) =>
        Cohttp_lwt.Body.to_string(body)
        >>= (
          body => {
            let anime =
              switch (anime_of_yojson(Yojson.Safe.from_string(body))) {
              | Ok(anime) => anime
              | Error(_) => failwith("Invalid url")
              };
            return(anime_response(anime));
          }
        )
    );
  };
  Lwt_main.run(fetch) |> ignore;
};
