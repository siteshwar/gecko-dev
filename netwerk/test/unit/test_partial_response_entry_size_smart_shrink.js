/*

  This is only a crash test.  We load a partial content, cache it.  Then we change the limit
  for single cache entry size (shrink it) so that the next request for the rest of the content
  will hit that limit and doom/remove the entry.  We change the size manually, but in reality
  it's being changed by cache smart size.

*/

Cu.import("resource://testing-common/httpd.js");
Cu.import("resource://gre/modules/Services.jsm");

XPCOMUtils.defineLazyGetter(this, "URL", function() {
  return "http://localhost:" + httpServer.identity.primaryPort;
});

var httpServer = null;

function make_channel(url, callback, ctx) {
  var ios = Cc["@mozilla.org/network/io-service;1"].
            getService(Ci.nsIIOService);
  return ios.newChannel(url, "", null);
}

// Have 2kb response (8 * 2 ^ 8)
var responseBody = "response";
for (var i = 0; i < 8; ++i) responseBody += responseBody;

function contentHandler(metadata, response)
{
  response.setHeader("Content-Type", "text/plain", false);
  response.setHeader("ETag", "range");
  response.setHeader("Accept-Ranges", "bytes");
  response.setHeader("Cache-Control", "max-age=360000");

  if (!metadata.hasHeader("If-Range")) {
    response.setHeader("Content-Length", responseBody.length + "");
    response.processAsync();
    var slice = responseBody.slice(0, 100);
    response.bodyOutputStream.write(slice, slice.length);
    response.finish();
  } else {
    var slice = responseBody.slice(100);
    response.setStatusLine(metadata.httpVersion, 206, "Partial Content");
    response.setHeader("Content-Range",
      (responseBody.length - slice.length).toString() + "-" +
      (responseBody.length - 1).toString() + "/" +
      (responseBody.length).toString());

    response.setHeader("Content-Length", slice.length + "");
    response.bodyOutputStream.write(slice, slice.length);
  }
}

function run_test()
{
  httpServer = new HttpServer();
  httpServer.registerPathHandler("/content", contentHandler);
  httpServer.start(-1);

  var chan = make_channel(URL + "/content");
  chan.asyncOpen(new ChannelListener(firstTimeThrough, null, CL_EXPECT_LATE_FAILURE), null);
  do_test_pending();
}

function firstTimeThrough(request, buffer)
{
  // Change single cache entry limit to 1 kb.  This emulates smart size change.
  Services.prefs.setIntPref("browser.cache.disk.max_entry_size", 1);

  var chan = make_channel(URL + "/content");
  chan.asyncOpen(new ChannelListener(finish_test, null), null);
}

function finish_test(request, buffer)
{
  do_check_eq(buffer, responseBody);
  httpServer.stop(do_test_finished);
}
