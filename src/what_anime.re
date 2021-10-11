open Cmdliner;

let anime_from_file = {
  let image_from_file = file => File_search.search_image_file(file);
  let file =
    Arg.(
      required & pos(0, some(string), None) & info([], ~docv="FILE PATH")
    );
  let doc = "search anime from file";
  let exits = Term.default_exits;
  (
    Term.(const(image_from_file) $ file),
    Term.info("file", ~doc, ~sdocs=Manpage.s_common_options, ~exits),
  );
};

let anime_from_link = {
  let image_from_link = link => Link_search.search_image_link(link);
  let link =
    Arg.(required & pos(0, some(string), None) & info([], ~docv="LINK"));
  let doc = "search anime from link";
  let exits = Term.default_exits;
  (
    Term.(const(image_from_link) $ link),
    Term.info("link", ~doc, ~sdocs=Manpage.s_common_options, ~exits),
  );
};

let default_cmd = {
  let doc = "Find anime scene with CLI from trace.moe. Inspired by: irevenko/what-anime-cli";
  let sdocs = Manpage.s_common_options;
  let exits = Term.default_exits;
  (
    Term.(ret(const(`Help((`Pager, None))))),
    Term.info("what-anime-cli", ~version="0.0.1", ~doc, ~sdocs, ~exits),
  );
};

let _ =
  Term.(
    exit @@ eval_choice(default_cmd, [anime_from_file, anime_from_link])
  );
